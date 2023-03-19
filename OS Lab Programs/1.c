// Implementation of basic UNIX commands using file APIs
// Write a program to implement commands ls( -l option), cp, rm and mv using
// UNIX file APIs. ls –l command
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

int main() {
  DIR *d;
  struct dirent *de;
  struct stat buf;
  int i, j;
  char P[10] = "rwxrwxrwx", AP[10] = " ";
  struct passwd *p;
  struct group *g;
  struct tm *t;
  char time[26];
  d = opendir(".");
  readdir(d);
  readdir(d);
  while ((de = readdir(d)) != NULL) {
    stat(de->d_name, &buf);
    // File Type
    if (S_ISDIR(buf.st_mode))
      printf("d");
    else if (S_ISREG(buf.st_mode))
      printf("-");
    else if (S_ISCHR(buf.st_mode))
      printf("c");
    else if (S_ISBLK(buf.st_mode))
      printf("b");
    else if (S_ISLNK(buf.st_mode))
      printf("l");
    else if (S_ISFIFO(buf.st_mode))
      printf("p");
    else if (S_ISSOCK(buf.st_mode))
      printf("s");
    // File Permissions P-Full Permissions AP-Actual Permissions
    for (i = 0, j = (1 << 8); i < 9; i++, j >>= 1)
      AP[i] = (buf.st_mode & j) ? P[i] : '-';
    printf("%s", AP);
    // No. of Hard Links
    printf("%5d", buf.st_nlink);
    // User Name
    p = getpwuid(buf.st_uid);
    printf(" %.8s", p->pw_name);
    // Group Name
    g = getgrgid(buf.st_gid);
    printf(" %-8.8s", g->gr_name);
    // File Size
    printf(" %8d", buf.st_size);
    // Date and Time of modification
    t = localtime(&buf.st_mtime);
    strftime(time, sizeof(time), "%b %d %H:%M", t);
    printf(" %s", time);
    // File Name
    printf(" %s\n", de->d_name);
  }
}

// cp command
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 8192
int main(int argc, char *argv[]) {
  int input_fd, output_fd; /* Input and output file descriptors */
  ssize_t ret_in, ret_out; /* Number of bytes returned by read() and write() */
  char buffer[BUF_SIZE];   /* Character buffer */
  /* Are src and dest file name arguments missing */
  if (argc != 3) {
    printf("Usage: cp file1 file2");
    return 1;
  }
  /* Create input file descriptor */
  input_fd = open(argv[1], O_RDONLY);
  if (input_fd == -1) {
    perror("open");
    return 2;
  }
  /* Create output file descriptor */
  output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
  if (output_fd == -1) {
    perror("open");
    return 3;
  }
  /* Copy process */
  while ((ret_in = read(input_fd, &buffer, BUF_SIZE)) > 0) {
    ret_out = write(output_fd, &buffer, (ssize_t)ret_in);
    if (ret_out != ret_in) {
      /* Write error */
      perror("write");
      return 4;
    }
  }
  /* Close file descriptors */
  close(input_fd);
  close(output_fd);
  return (EXIT_SUCCESS);
}

// mv command
int main(int argc, char *argv[]) {
  int input_fd, output_fd; /* Input and output file descriptors */
  /* Are src and dest file name arguments missing */
  if (argc != 3) {
    printf("Usage: mv file1 file2");
    return 1;
  }
  /* Create input file descriptor */
  input_fd = link(argv[1], argv[2]);
  if (input_fd == -1) {
    perror("link error");
    return 2;
  }
  /* Create output file descriptor */
  output_fd = unlink(argv[1]);
  if (output_fd == -1) {
    perror("unlink");
    return 3;
  }
}

// srm command
int main(int argc, char *argv[]) {
  output_fd = unlink(argv[1]);
  if (output_fd == -1) {
    perror("unlink error");
    return 3;
  }
}
