#include "p101_database/database.h"
#include <p101_env/wrapper.h>

static int dbm_error_code(int saved_errno);

static int dbm_error_code(int saved_errno)
{
    if(saved_errno == 0)
    {
        saved_errno = EIO;
    }

    return saved_errno;
}

void p101_dbm_clearerr(const struct p101_env *env, DBM *db)
{
    P101_TRACE(env);
    errno = 0;
    dbm_clearerr(db);
    P101_TRACE_EXIT(env);
}

void p101_dbm_close(const struct p101_env *env, DBM *db)
{
    P101_TRACE(env);
    errno = 0;
    dbm_close(db);
    P101_TRACK_POINTER_RESOURCE_RELEASE(env, "ndbm-database", db, NULL);
    P101_TRACE_EXIT(env);
}

int p101_dbm_delete(const struct p101_env *env, struct p101_error *err, DBM *db, datum key)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = dbm_delete(db, key);

    if(ret_val < 0)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(errno));
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_dbm_error(const struct p101_env *env, DBM *db)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_error(db);

    P101_TRACE_EXIT(env);
    return ret_val;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_fetch(const struct p101_env *env, struct p101_error *err, DBM *db, datum key)
{
    int   saved_errno;
    datum ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ((datum){.dptr = NULL, .dsize = 0}));
    p101_dbm_clearerr(env, db);
    errno       = 0;
    ret_val     = dbm_fetch(db, key);
    saved_errno = errno;

    if(ret_val.dptr == NULL && p101_dbm_error(env, db) != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(saved_errno));
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_firstkey(const struct p101_env *env, struct p101_error *err, DBM *db)
{
    int   saved_errno;
    datum ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ((datum){.dptr = NULL, .dsize = 0}));
    p101_dbm_clearerr(env, db);
    errno       = 0;
    ret_val     = dbm_firstkey(db);
    saved_errno = errno;

    if(ret_val.dptr == NULL && p101_dbm_error(env, db) != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(saved_errno));
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_nextkey(const struct p101_env *env, struct p101_error *err, DBM *db)
{
    int   saved_errno;
    datum ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, ((datum){.dptr = NULL, .dsize = 0}));
    p101_dbm_clearerr(env, db);
    errno       = 0;
    ret_val     = dbm_nextkey(db);
    saved_errno = errno;

    if(ret_val.dptr == NULL && p101_dbm_error(env, db) != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(saved_errno));
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

#pragma GCC diagnostic pop

DBM *p101_dbm_open(const struct p101_env *env, struct p101_error *err, const char *file, int open_flags, mode_t file_mode)
{
    DBM *ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, NULL);
    errno = 0;
#pragma GCC diagnostic push
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#endif
#ifdef __clang__
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
#endif
    ret_val = dbm_open(file,
                       open_flags,
#ifdef __linux__
                       (int)
#endif
                           file_mode);
#pragma GCC diagnostic pop

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(errno));
    }
    else
    {
        P101_TRACK_POINTER_RESOURCE_ACQUIRE(env, "ndbm-database", ret_val, 0U, file);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_dbm_store(const struct p101_env *env, struct p101_error *err, DBM *db, datum key, datum content, int store_mode)
{
    int ret_val;

    P101_TRACE(env);
    P101_WRAPPER_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = dbm_store(db, key, content, store_mode);

    if(ret_val < 0)
    {
        P101_ERROR_RAISE_ERRNO(err, dbm_error_code(errno));
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
