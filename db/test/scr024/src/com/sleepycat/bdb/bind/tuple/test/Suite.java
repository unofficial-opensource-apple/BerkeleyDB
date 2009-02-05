/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2002-2003
 *	Sleepycat Software.  All rights reserved.
 *
 * $Id: Suite.java,v 1.2 2004/03/30 01:24:44 jtownsen Exp $
 */

package com.sleepycat.bdb.bind.tuple.test;

import junit.framework.Test;
import junit.framework.TestSuite;

/**
 * @author Mark Hayes
 */
public class Suite {

    public static void main(String[] args)
        throws Exception {

        junit.textui.TestRunner.run(suite());
    }

    public static Test suite()
        throws Exception {

        TestSuite suite = new TestSuite();
        suite.addTest(TupleFormatTest.suite());
        suite.addTest(TupleOrderingTest.suite());
        suite.addTest(TupleBindingTest.suite());
        return suite;
    }
}

