#include <dirent.h>
#include <fcntl.h>
#include <limits.h>
#include <p101_database/p101_ndbm.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

static void remove_database_directory(const char *directory_path)
{
    DIR           *directory;
    struct dirent *entry;
    char           path[PATH_MAX];

    directory = opendir(directory_path);
    if(directory == NULL)
    {
        return;
    }
    while((entry = readdir(directory)) != NULL)
    {
        if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }
        if(snprintf(path, sizeof(path), "%s/%s", directory_path, entry->d_name) > 0)
        {
            (void)unlink(path);
        }
    }
    (void)closedir(directory);
    (void)rmdir(directory_path);
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;
    char               directory[] = "/tmp/p101-dbm-test-XXXXXX";
    char               path[PATH_MAX];
    DBM               *database;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }
    EXPECT(mkdtemp(directory) != NULL);
    EXPECT(snprintf(path, sizeof(path), "%s/database", directory) > 0);
    database = p101_dbm_open(env, err, path, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    EXPECT(database != NULL);
    EXPECT(p101_error_has_no_error(err));
    if(database != NULL)
    {
        /* P101_TEST_CASE(p101_dbm_error) */
        EXPECT(p101_dbm_error(env, database) == 0);
        /* P101_TEST_CASE(p101_dbm_clearerr) */
        p101_dbm_clearerr(env, database);
        /* P101_TEST_CASE(p101_dbm_close) */
        p101_dbm_close(env, database);
    }
    remove_database_directory(directory);
    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
