from setuptools import setup

setup(name='HEPTools',
      version='0.1',
      description='A collection of tools that are helpful to me during my PhD in Particle Physics at MIT.',
      url='https://github.com/weissercn/HEPTools',
      author='Constantin Weisser',
      author_email='weissercn@gmail.com',
      license='MIT',
      packages=['HEPTools', 'HEPTools/matplotlib_stylesheet'],
      install_requires=[
          'numpy',
          'scipy',
          'scikit-learn',
          'keras',
          'adaptive_binning_chisquared_2sam',
      ],
      zip_safe=False)

