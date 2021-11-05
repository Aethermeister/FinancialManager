TEMPLATE = subdirs

SUBDIRS = \
            FinancialManager \
            FinancialManagerLibrary \
            FinancialManagerAutoTest

FinancialManager.depends = FinancialManagerLibrary
FinancialManagerAutoTest.depends = FinancialManagerLibrary
