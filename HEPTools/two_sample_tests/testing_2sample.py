#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#
#
# Name:     testing_2sample.py 
#
# Author:   Constantin Weisser (weisser@mit.edu)
#
# Purpose:  This file is used to test the implementation of 
#	    cramer_von_mises_2sample.py  
#
#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#-#


from scipy import stats
import numpy as np
import cramer_von_mises_2sample as cr

def testing_2sample():
	np.random.seed(12345678)
	n1 = 200  # size of first sample
	n2 = 300  # size of second sample
	rvs1 = stats.norm.rvs(size=n1, loc=0., scale=1)
	rvs2 = stats.norm.rvs(size=n2, loc=0.5, scale=1.5)

	print(stats.ks_2samp(rvs1, rvs2))
	print(cr.ks_2samp(rvs1,rvs2))
	print(cr.cvm_2samp(rvs1,rvs2))

	rvs3 = stats.norm.rvs(size=n2, loc=0.01, scale=1.0)
	print(stats.ks_2samp(rvs1, rvs3))
	print(cr.ks_2samp(rvs1,rvs3))
	print(cr.cvm_2samp(rvs1,rvs3))

	rvs4 = stats.norm.rvs(size=n2, loc=0.0, scale=1.0)

	print(stats.ks_2samp(rvs1, rvs4))
	print(cr.ks_2samp(rvs1,rvs4))
	print(cr.cvm_2samp(rvs1,rvs4))

	rvs5 = stats.norm.rvs(size=n2, loc=20, scale=1.5)


	print(stats.ks_2samp(rvs1, rvs5))
	print(cr.ks_2samp(rvs1,rvs5))
	print(cr.cvm_2samp(rvs1,rvs5))


