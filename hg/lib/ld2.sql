# ld2.sql was originally generated by the autoSql program, which also 
# generated ld2.c and ld2.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Linkage Disequilibrium values computed by Haploview and encoded by UCSC.
CREATE TABLE ld2 (
    bin smallint not null,      # Bin number for browser speedup
    chrom varchar(255) not null,	# Reference sequence chromosome or scaffold
    chromStart int unsigned not null,	# chromStart for reference marker
    chromEnd int unsigned not null,	# chromEnd for last marker in list
    name varchar(255) not null,	# rsId at chromStart
    ldCount int unsigned not null,	# Number of markers with LD values
    dprime longblob not null,	# Encoded list (length=ldCount) of D' values
    rsquared longblob not null,	# Encoded list (length=ldCount) of r^2 values
    lod longblob not null,	# Encoded list (length=ldCount) of LOD values
    avgDprime char(1) not null,	# Encoded average D' magnitude for dense display
    avgRsquared char(1) not null,	# Encoded average r^2 value for dense display
    avgLod char(1) not null,	# Encoded average LOD value for dense display
    tInt char(1) not null,	# Encoded T-int value between this and next marker
              #Indices
    INDEX(chrom,bin)
);
