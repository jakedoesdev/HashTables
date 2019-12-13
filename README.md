Created by myself and three other students as a CSCE2110 project at the University of North Texas in Fall 2019. My contribution was the hash table that handles the geography table.
I use modulo hashing with linear probing as a collision strategy.

Upon execution, this program requests the name of an input file from the user. The first three lines of this input file will each contain the name of a .csv file followed by
a space followed by the name of the table to be created with the table data.

The line following the last .csv filename will be blank. All remaining lines will be INSERT, UPDATE, SELECT, or DELETE queries to be performed on the data. The format of these
queries is: QUERY(string, string) where the first string is a tuple of table values and the second string is the table name. SELECT and DELETE queries will accept * as a
wildcard table value.

The program will perform 3 different types of 

Table schemas:


Age:
string   ,int    ,int     ,int
geo_geoid,under_5,under_18,over_65

Disability:
string  ,int 		       ,int 			 ,int                 ,int                  ,int                  ,int
geo_name,hearing_disability,vision_disability,cognitive_disability,ambulatory_disability,self_care_disability,independent_living_disability

Geography:
int			  ,string  ,string       ,int        ,int  ,int       ,string   ,int
(key)replan_id,geo_name,geo_stusab,geo_sumlev,geo_state,geo_county,geo_geoid,population