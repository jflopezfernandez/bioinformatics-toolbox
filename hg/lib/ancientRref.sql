# ancientRref.sql was originally generated by the autoSql program, which also 
# generated ancientRref.c and ancientRref.h.  This creates the database representation of
# an object which can be loaded and saved from RAM in a fairly 
# automatic way.

#Reference table for details page of human/mouse ancient repeat track.
CREATE TABLE ancientRref (
    id varchar(255) not null,	# Unique id for each repeat
    name longblob not null,	# human repeat name 
    class longblob not null,	# repeat class
    family longblob not null,	# repeat family
    hseq longblob not null,	# Human sequence with gaps
    mseq longblob not null,	# mouse sequence with gaps
              #Indices
    PRIMARY KEY(id)
);
