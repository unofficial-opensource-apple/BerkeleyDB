/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2000-2003
 *      Sleepycat Software.  All rights reserved.
 *
 * $Id: ExceptionWrapper.java,v 1.2 2004/03/30 01:23:36 jtownsen Exp $
 */

package com.sleepycat.bdb.util;

/**
 * Interface implemented by exceptions that can contain nested exceptions.
 *
 * @author Mark Hayes
 */
public interface ExceptionWrapper {

    /**
     * Returns the nested exception or null if none is present.
     *
     * @return the nested exception or null if none is present.
     */
    Throwable getDetail();
}
