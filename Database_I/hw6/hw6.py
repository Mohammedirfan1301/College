import pandas
import sqlite3

# for the csv file, first line should be the column names and all lines after should be the data
# for example:
# name,class,launched
# California,Tennessee,1921

conn = sqlite3.connect('hw.db')
table_name = "Product"  # name table here
df = pandas.read_csv('table.csv')
df.to_sql(table_name, conn, if_exists='append', index=False)
