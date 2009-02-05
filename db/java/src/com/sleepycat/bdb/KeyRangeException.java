/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2000-2003
 *      Sleepycat Software.  All rights reserved.
 *
 * $Id: KeyRangeException.java,v 1.2 2004/03/30 01:23:29 jtownsen Exp $
 */

package com.sleepycat.bdb;

/**
 * (<em>internal</em>) An exception thrown when a key is out of range.
 *
 * <p><b>NOTE:</b> This classes is internal and may be changed incompatibly or
 * deleted in the future.  It is public only so it may be used by
 * subpackages.</p>
 *
 * @author Mark Hayes
 */
public class KeyRangeException extends IllegalArgumentException {

    /**
     * Creates a key range exception.
     */
    public KeyRangeException(String msg) {

        super(msg);
    }
}

