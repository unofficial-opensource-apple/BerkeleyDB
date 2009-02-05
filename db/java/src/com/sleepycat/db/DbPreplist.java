/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1999-2002
 *      Sleepycat Software.  All rights reserved.
 *
 * $Id: DbPreplist.java,v 1.1.1.1 2003/02/15 04:56:07 zarzycki Exp $
 */

package com.sleepycat.db;

/*
 * This is filled in and returned by the
 * DbEnv.txn_recover() method.
 */
public class DbPreplist
{
    public DbTxn txn;
    public byte gid[];
}

// end of DbPreplist.java
