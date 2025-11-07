#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>

#include "process_reader.h"
#include "utils.h"

#define DEFAULT_MAX_PROCS 20

/* Exclude background/system daemons and kernel threads */
static const char *IGNORED_KEYWORDS[] = {
    "systemd", "kthreadd", "rcu_", "migration", "watchdog",
    "dbus", "sshd", "kworker", "ksoftirqd", "journald",
    "pipewire", "Xorg", "gnome-", "snapd", "polkitd",
    "avahi", "cupsd", "colord", "irq", "NetworkManager",
    "bluetoothd", "fwupd", "tracker", "upowerd",
    "idle_inject", "cpu", "kdevtmpfs", "kcompactd", "ata_sff",
    NULL
};

static int is_ignored_process(const char *name) {
    if (!name || name[0] == '\0') return 1;
    if (name[0] == '[') return 1;  // kernel threads
    for (int i = 0; IGNORED_KEYWORDS[i]; i++) {
        if (strstr(name, IGNORED_KEYWORDS[i]) != NULL)
            return 1;
    }
    return 0;
}

static int read_comm(pid_t pid, char *out, size_t out_size) {
    char path[256];
    snprintf(path, sizeof(path), "/proc/%d/comm", pid);
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    if (!fgets(out, out_size, f)) { fclose(f); return -1; }
    out[strcspn(out, "\n")] = '\0';
    fclose(f);
    return 0;
}

static double read_cpu_seconds(pid_t pid) {
    char path[256], buf[2048];
    snprintf(path, sizeof(path), "/proc/%d/stat", pid);
    FILE *f = fopen(path, "r");
    if (!f) return 0.0;
    if (!fgets(buf, sizeof(buf), f)) { fclose(f); return 0.0; }
    fclose(f);

    char *rp = strrchr(buf, ')');
    if (!rp) return 0.0;
    char *rest = rp + 2;

    long utime = 0, stime = 0;
    char *saveptr = NULL;
    char *tok = strtok_r(rest, " ", &saveptr);
    int idx = 1;
    while (tok) {
        if (idx == 13) utime = atol(tok);
        if (idx == 14) { stime = atol(tok); break; }
        tok = strtok_r(NULL, " ", &saveptr);
        idx++;
    }
    long clk = sysconf(_SC_CLK_TCK);
    if (clk <= 0) clk = 100;
    return (double)(utime + stime) / (double)clk;
}

static void read_uid_nice(pid_t pid, uid_t *out_uid, int *out_nice) {
    char path[256], line[256];
    snprintf(path, sizeof(path), "/proc/%d/status", pid);
    FILE *f = fopen(path, "r");
    if (!f) { *out_uid = (uid_t)-1; *out_nice = 0; return; }
    *out_uid = (uid_t)-1;
    *out_nice = 0;
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "Uid:", 4) == 0) {
            unsigned int real = 0;
            if (sscanf(line+4, "%u", &real) == 1) *out_uid = (uid_t)real;
        } else if (strncmp(line, "Nice:", 5) == 0) {
            int nz;
            if (sscanf(line+5, "%d", &nz) == 1) *out_nice = nz;
        }
    }
    fclose(f);
}

/* Fetch processes */
int read_processes(proc_info *procs, int max_procs) {
    if (!procs) return 0;
    if (max_procs <= 0) max_procs = DEFAULT_MAX_PROCS;

    DIR *d = opendir("/proc");
    if (!d) {
        perror("opendir(/proc)");
        return 0;
    }

    struct dirent *ent;
    int count = 0;
    while ((ent = readdir(d)) != NULL && count < max_procs * 5) { // read more, filter later
        if (!isdigit(ent->d_name[0])) continue;
        pid_t pid = (pid_t)atoi(ent->d_name);

        char comm[NAME_LEN];
        if (read_comm(pid, comm, sizeof(comm)) != 0) continue;
        if (is_ignored_process(comm)) continue;

        proc_info p;
        memset(&p, 0, sizeof(p));
        p.pid = pid;
        strncpy(p.name, comm, NAME_LEN-1);
        p.state = '?';
        p.cpu_seconds = read_cpu_seconds(pid);
        read_uid_nice(pid, &p.uid, &p.nice);
        p.burst_estimate = p.cpu_seconds > 0.0 ? p.cpu_seconds : (double)(rand() % 10 + 1);

        procs[count++] = p;
        if (count >= max_procs) break;
    }
    closedir(d);
    return count;
}

void print_process_summary(const proc_info *procs, int count) {
    print_process_table(procs, count);
}

