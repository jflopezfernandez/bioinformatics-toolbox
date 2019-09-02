# itemAttr.sql was originally generated by the autoSql program, which also 
# generated itemAttr.c and itemAttr.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Relational object of display attributes for individual track items
CREATE TABLE itemAttr (
    name varchar(255) not null,	# name of item
    chrom varchar(255) not null,	# chromosome
    chromStart int unsigned not null,	# Start position in chromosome
    chromEnd int unsigned not null,	# End position in chromosome
    colorR tinyint unsigned not null,	# Color red component 0-255
    colorG tinyint unsigned not null,	# Color green component 0-255
    colorB tinyint unsigned not null,	# Color blue component 0-255
              #Indices
    INDEX(name)
);
