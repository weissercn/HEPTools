#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#
# Name:     cramer_von_mises_2sample.py
#
# Author:   Constantin Weisser (weisser@mit.edu)
#
# Purpose:  The ks_2samp method was directly taken from numpy and the cvm_2samp
#           method was implemented using T.W. Andersons "On the distribution
#	    of the two-sample Cramer von Mises Criterion
#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-# 


from __future__ import division, print_function
import numpy as np
#Taken directly from scipy


import warnings
import math
from collections import namedtuple

#from scipy.lib.six import xrange

# friedmanchisquare patch uses python sum
pysum = sum  # save it before it gets overwritten

# Scipy imports.
#from scipy.lib.six import callable, string_types
from numpy import array, asarray, ma, zeros, sum
import scipy.stats
import numpy as np






def ks_2samp(data1, data2):
    """
    Computes the Kolmogorov-Smirnov statistic on 2 samples.
    This is a two-sided test for the null hypothesis that 2 independent samples
    are drawn from the same continuous distribution.
    Parameters
    ----------
    a, b : sequence of 1-D ndarrays
        two arrays of sample observations assumed to be drawn from a continuous
        distribution, sample sizes can be different
    Returns
    -------
    D : float
        KS statistic
    p-value : float
        two-tailed p-value
    Notes
    -----
    This tests whether 2 samples are drawn from the same distribution. Note
    that, like in the case of the one-sample K-S test, the distribution is
    assumed to be continuous.
    This is the two-sided test, one-sided tests are not implemented.
    The test uses the two-sided asymptotic Kolmogorov-Smirnov distribution.
    If the K-S statistic is small or the p-value is high, then we cannot
    reject the hypothesis that the distributions of the two samples
    are the same.
    Examples
    --------
    >>> from scipy import stats
    >>> np.random.seed(12345678)  #fix random seed to get the same result
    >>> n1 = 200  # size of first sample
    >>> n2 = 300  # size of second sample
    For a different distribution, we can reject the null hypothesis since the
    pvalue is below 1%:
    >>> rvs1 = stats.norm.rvs(size=n1, loc=0., scale=1)
    >>> rvs2 = stats.norm.rvs(size=n2, loc=0.5, scale=1.5)
    >>> stats.ks_2samp(rvs1, rvs2)
    (0.20833333333333337, 4.6674975515806989e-005)
    For a slightly different distribution, we cannot reject the null hypothesis
    at a 10% or lower alpha since the p-value at 0.144 is higher than 10%
    >>> rvs3 = stats.norm.rvs(size=n2, loc=0.01, scale=1.0)
    >>> stats.ks_2samp(rvs1, rvs3)
    (0.10333333333333333, 0.14498781825751686)
    For an identical distribution, we cannot reject the null hypothesis since
    the p-value is high, 41%:
    >>> rvs4 = stats.norm.rvs(size=n2, loc=0.0, scale=1.0)
    >>> stats.ks_2samp(rvs1, rvs4)
    (0.07999999999999996, 0.41126949729859719)
    """
    data1, data2 = map(asarray, (data1, data2))
    n1 = data1.shape[0]
    n2 = data2.shape[0]
    n1 = len(data1)
    n2 = len(data2)
    data1 = np.sort(data1)
    data2 = np.sort(data2)
    data_all = np.concatenate([data1,data2])
    cdf1 = np.searchsorted(data1,data_all,side='right')/(1.0*n1)
    cdf2 = (np.searchsorted(data2,data_all,side='right'))/(1.0*n2)
    d = np.max(np.absolute(cdf1-cdf2))
    # Note: d absolute not signed distance
    en = np.sqrt(n1*n2/float(n1+n2))

    try:
        prob = scipy.stats.kstwobign.sf((en + 0.12 + 0.11 / en) * d)
    except:
        prob = 1.0
    return d, prob

def cvm_2samp(data1, data2):
    """
    Performs the Cramer von Mises two sample test and returns the 
    U and the T value.
    """
 
    data1, data2 = map(asarray, (data1, data2))
    n1 = data1.shape[0]
    n2 = data2.shape[0]
    n1 = len(data1)
    n2 = len(data2)
    data1 = np.sort(data1)
    data2 = np.sort(data2)


    data_all = np.concatenate([data1,data2])
    data_all = np.sort(data_all)
    ranks1 = np.searchsorted(data_all,data1)
    ranks2 = np.searchsorted(data_all,data2)

    U_N_contrib = 0
    for i in range(0,n1):
	U_N_contrib += np.square(ranks1[i]-i) 


    U_M_contrib = 0
    for j in range(0,n2):
	U_M_contrib +=np.square(ranks2[j]-j)

    U=n1*U_N_contrib + n2*U_M_contrib

    T=U/(n1*n2*(n1+n2))- (4*n1*n2-1)/(6*(n1+n2))


    return U,T
