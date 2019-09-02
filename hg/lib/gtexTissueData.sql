# gtexTissueData.sql was originally generated by the autoSql program, which also 
# generated gtexTissueData.c and gtexTissueData.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#GTEX Expression data summarized by tissue (RPKM)
CREATE TABLE gtexTissueData (
    geneId varchar(255) not null,	# Gene identifier (ensembl)
    tissue varchar(255) not null,	# Tissue short name
    min double not null,	# Minimum expression level
    q1 double not null,	# 1st quartile expression level
    median double not null,	# Median expression level
    q3 double not null,	# 3rd quartile expression level
    max double not null,	# Maximum expression level
              #Indices
    INDEX(geneId),
    INDEX(tissue)
);
