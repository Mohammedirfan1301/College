import pandas
import sqlite3

# for the csv file, first line should be the column names and all lines after should be the data
# for example:
# name,class,launched
# California,Tennessee,1921

# DB here
conn = sqlite3.connect('hw.db')

# Table "Product"
table = "Product"  # name table here
df = pandas.read_csv('product.csv')
df.to_sql(table, conn, if_exists='append', index=False)

# Table "PC"
table = "PC"  # name table here
df = pandas.read_csv('pc.csv')
df.to_sql(table, conn, if_exists='append', index=False)

# Table "Laptop"
table = "Laptop"  # name table here
df = pandas.read_csv('laptop.csv')
df.to_sql(table, conn, if_exists='append', index=False)

# Table "Printer"
table = "Printer"  # name table here
df = pandas.read_csv('printer.csv')
df.to_sql(table, conn, if_exists='append', index=False)
