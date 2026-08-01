#include <errno.h>
#include <p101_database/database.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <stdio.h>
#include <stdlib.h>

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

struct fault_state
{
    int checks;
    int errnum;
};

static int fail_next_call(const struct p101_env *env, const char *call_name, void *user_data)
{
    struct fault_state *state;

    (void)env;
    (void)call_name;
    state = user_data;
    state->checks++;
    return state->errnum;
}

/* P101_TEST_CASE(p101_dbm_delete) */
static void test_p101_dbm_delete(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_dbm_delete(env, err, NULL, (datum){0});
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_dbm_fetch) */
static void test_p101_dbm_fetch(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        datum result = p101_dbm_fetch(env, err, NULL, (datum){0});
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_dbm_firstkey) */
static void test_p101_dbm_firstkey(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        datum result = p101_dbm_firstkey(env, err, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_dbm_nextkey) */
static void test_p101_dbm_nextkey(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        datum result = p101_dbm_nextkey(env, err, NULL);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_dbm_open) */
static void test_p101_dbm_open(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        DBM *result = p101_dbm_open(env, err, NULL, 0, 0);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

/* P101_TEST_CASE(p101_dbm_store) */
static void test_p101_dbm_store(struct p101_env *env, struct p101_error *err)
{
#ifdef __linux__
    static const int errors[] = {EIO};
#elif defined(__APPLE__)
    static const int errors[] = {EIO};
#elif defined(__FreeBSD__)
    static const int errors[] = {EIO};
#else
    static const int errors[] = {EIO};
#endif

    for(size_t index = 0U; index < sizeof(errors) / sizeof(errors[0]); index++)
    {
        struct fault_state state = {0, errors[index]};

        p101_env_set_fault_injector(env, fail_next_call, &state);
        int result = p101_dbm_store(env, err, NULL, (datum){0}, (datum){0}, 0);
        (void)result;
        EXPECT(state.checks == 1);
        EXPECT(p101_error_is_errno(err, state.errnum));
        p101_error_reset(err);
    }
    p101_env_set_fault_injector(env, NULL, NULL);
}

int main(void)
{
    struct p101_error *err;
    struct p101_env   *env;

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
    test_p101_dbm_delete(env, err);
    test_p101_dbm_fetch(env, err);
    test_p101_dbm_firstkey(env, err);
    test_p101_dbm_nextkey(env, err);
    test_p101_dbm_open(env, err);
    test_p101_dbm_store(env, err);
    p101_env_destroy(env);
    p101_error_destroy(err);
    return failures == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
