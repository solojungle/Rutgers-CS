from sqlalchemy import create_engine
from sqlalchemy import sql
import datetime
import json

from BarBeerDrinker import config

engine = create_engine(config.database_uri)

def get_bars_general():
        with engine.connect() as con:
                rs = con.execute("SELECT * FROM bar;")
                results = [dict(row) for row in rs]
                for r in results:
                        r['open'] ="{}".format( r['open'])
                        r['close'] = "{}".format(r['close']) 
                return results



def get_bars(barID):
        with engine.connect() as con:
                rs = con.execute("SELECT * FROM bar WHERE bar_id = '"+barID+"\'")
                results = [dict(row) for row in rs]
                for r in results:
                        r['open'] ="{}".format( r['open'])
                        r['close'] = "{}".format(r['close']) 
                return results

def get_top_drinkers(barID):
        with engine.connect() as con:
                rs = con.execute("SELECT drinker.first, drinker.last, SUM(grand_total) as sum FROM bill, drinker WHERE bar_id = '"+ barID +"\' AND drinker.drinker_id = bill.drinker_id \
                group by bill.drinker_id \
                order by sum desc limit 5")
                results = [dict(row) for row in rs]
                for r in results:
                        r['sum'] = float(r['sum'])
                return results

def get_top_manf(barID):
        with engine.connect() as con:
                rs = con.execute("SELECT item.manf, count(manf) as num_beers_sold_by_manf FROM bill, orders, item "
                "WHERE bill.bar_id = '"+barID+"\' "
                "AND orders.bill_id = bill.bill_id AND item.name = orders.item "
                "AND item.category = 'beer' "
               " group by manf "
                "order by num_beers_sold_by_manf desc "
                "limit 5")
                results = [dict(row) for row in rs]

                return results

def get_bill_times(barID):
        with engine.connect() as con:
                rs = con.execute("SELECT count(*) as num_of_orders, HOUR(time) as hour FROM orders, bill " 
                "WHERE bill.bar_id = '"+barID+"' AND bill.bill_id = orders.bill_id "
                "group by hour")

                results = [dict(row) for row in rs]
               
                return results

def get_beers():
        with engine.connect() as con:
                rs = con.execute("Select name, manf from item WHERE category = 'beer'")
                results = [dict(row) for row in rs]
                return results

def get_popular_beers(barID):
        with engine.connect() as con:
                rs = con.execute(
                "SELECT item, count(item) FROM item, orders, "
                "(SELECT bill_id FROM bill WHERE bar_id = '"+barID+"\')barBill "
                "WHERE orders.bill_id = barBill.bill_id AND item.name = orders.item AND item.category = 'beer' "
                "group by item order by count(item) desc limit 5")
                results = [dict(row) for row in rs]
                return results

def get_beer(name):
        with engine.connect() as con:
                rs = con.execute("SELECT * FROM item WHERE category = 'beer' AND name = '"+name+"\'")
                results = [dict(row) for row in rs]
                return results

def get_beer_popularity(name):
        with engine.connect() as con:
                rs = con.execute("SELECT bar.name, count(*) as num_of_sales FROM orders, bill, bar WHERE item = '"+name+"\' "
                "AND orders.bill_id = bill.bill_id AND bill.bar_id = bar.bar_id "
                "group by bill.bar_id "
                "order by count(*) desc "
                "limit 5")
                results = [dict(row) for row in rs]
                return results

def get_drinkers():
        with engine.connect() as con:
                rs = con.execute("Select * from drinker")
                results = [dict(row) for row in rs]
                return results

def get_drinker(drinkerID):
        with engine.connect() as con:
                rs = con.execute("Select * from drinker WHERE drinker_id = '"+drinkerID+"\'" )
                results = [dict(row) for row in rs]
                return results

def busiest_dayofweek(barID):
        with engine.connect() as con:
                rs = con.execute("SELECT DAYOFWEEK(date) as day_of_week, count(date) as num_of_orders "
                "FROM bill WHERE bill.bar_id = '"+barID+"\'" 
                "group by day_of_week" )
                results = [dict(row) for row in rs]
                return results

def get_drinker_bills(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT bill.bill_id, bar.name, tip, tax, total, time, date, grand_total FROM bill, bar "
                "WHERE bill.drinker_id = '"+drinkerID+"\' AND bar.bar_id = bill.bar_id "
                "order by bill.time")
                results = [dict(row) for row in rs]
                for r in results:
                        r['tip'] = float(r['tip'])
                        r['tax'] = float(r['tax'])  
                        r['grand_total'] = float(r['grand_total'])
                        r['total'] = float(r['total'])
                        r['time'] = str(r['time'])
                        r['date'] = str(r['date'])
                     
                        
                return results

def get_orders_forbill(billID):
        with engine.connect() as con:
                rs = con.execute("SELECT * from orders "
                "WHERE bill_id = '"+billID+"\'" )
                results = [dict(row) for row in rs]
                for r in results:
                        r['price'] = float(r['price'])
                return results

def get_beers_ordered_most(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT orders.item, count(*) as num_of_orders from bill, orders, item WHERE bill.drinker_id = '"+drinkerID+"\' "
                "AND orders.bill_id = bill.bill_id AND orders.item = item.name AND item.category = 'beer' "
                "group by orders.item "
                "order by num_of_orders desc "
                "limit 5")
                results = [dict(row) for row in rs]
               
                return results

def get_biggest_consumer(name):
        with engine.connect() as con:
                rs = con.execute("SELECT drinker.first, drinker.last, count(*) as num_of_orders "
                "FROM orders, bill, drinker "
                "WHERE item = '"+name+"\' "
                "AND orders.bill_id = bill.bill_id AND bill.drinker_id = drinker.drinker_id "
                "group by bill.drinker_id "
                "order by num_of_orders desc "
                "limit 5")
                results = [dict(row) for row in rs]
               
                return results

def get_times_beer_sells_most(name):
        with engine.connect() as con:
                rs = con.execute("SELECT hour(time) as hour, count(*) as num_of_orders "
                "FROM orders, bill WHERE orders.item = '"+name+"\' "
                "AND orders.bill_id = bill.bill_id "
                "group by hour(time) "
                "order by time")
                results = [dict(row) for row in rs]
               
                return results

def get_spending_bydate(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT date, sum(grand_total) as spending_during_date "
                "FROM bill "
                "WHERE bill.drinker_id = '"+drinkerID+"\' "
                "group by date")
                results = [dict(row) for row in rs]
                for r in results:
                        r['spending_during_date'] = float(r['spending_during_date'])
                        r['date'] = str(r['date'])
               
                return results

def get_spending_bymonth(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT MONTH(date) as month, sum(grand_total) as spending_during_month "
                "FROM bill "
                "WHERE bill.drinker_id = '"+drinkerID+"\' "
                "group by MONTH(date)")

                results = [dict(row) for row in rs]
                for r in results:
                        r['spending_during_month'] = float(r['spending_during_month'])
               
                return results

def get_spending_byweek(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT WEEK(date) as week_num, sum(grand_total) as spending_during_week "
                "FROM bill "
                "WHERE bill.drinker_id = '"+drinkerID+"\' "
                "group by WEEK(date)")

                results = [dict(row) for row in rs]
                for r in results:
                        r['spending_during_week'] = float(r['spending_during_week'])
               
                return results

def insert_drinker(first, last, addr, city, state, zip, phone):
        with engine.connect() as con:
                
                check = con.execute("SELECT * FROM drinker WHERE first = '"+first+"\' AND last = '"+last+"\' "
                "AND addr = '"+addr+"\' AND city =  '"+city+"\' AND state = '"+state+"\' "
                "AND zip = '"+zip+"\' AND phone = '"+phone+"\'")

                results = [dict(row) for row in check] 
                if results is not None:
                        return False

                rs = con.execute("INSERT INTO drinker (first, last, addr, city, state, zip, phone) "
                "VALUES ('"+first+"\', '"+last+"\', '"+addr+"\', '"+city+"\', '"+state+"\','"+zip+"\','"+phone+"\') ")
                
                return True

def get_allbars_drinkerorders_from(drinkerID):
        with engine.connect() as con:
                rs = con.execute("SELECT bar.name FROM bill, bar WHERE drinker_id = '"+drinkerID+"\' "
                "AND bill.bar_id = bar.bar_id")
                results = [dict(row) for row in rs]
               
                return results

def insert_drinkerquery(query):
         with engine.connect() as con:
                rs = con.execute(query)
               
                return True

def sql_box(query):
        with engine.connect() as con:
                rs = con.execute(query)

                results = [dict(row) for row in rs]
                for r in results:
                        for val in r:
                                r[val] = str(r[val])
                
                
                return results

def verify_frequents():
        with engine.connect() as con:
                rs = con.execute("SELECT "
                "IF((SELECT " 
                "frequents.drinker_id "
                "FROM "
                "((frequents "
                "INNER JOIN bar ON frequents.bar_id = bar.bar_id) "
                "INNER JOIN drinker ON frequents.drinker_id = drinker.drinker_id) "
                "WHERE "
                "bar.state != drinker.state) IS NULL, "
                "TRUE, "
                "FALSE) as verify")

                results = [dict(row) for row in rs]
                
                
                return results

def verify_operating_hours():
        with engine.connect() as con:
                rs = con.execute("SELECT "
                "IF((SELECT "
                "bill.bill_id "
                "FROM "
                "bill "
                "LEFT JOIN "
                "bar ON bill.bar_id = bar.bar_id "
                "WHERE "
                "bill.time < bar.open "
                "OR !( (bar.open > bar.close "
                "AND bill.time > bar.close) "
                "OR (bar.open < bar.close "
                "AND bill.time < bar.close))) IS NULL, "
                "TRUE, "
                "FALSE) as verify")

                results = [dict(row) for row in rs]
                
                return results

def verify_beer_constraint():
        with engine.connect() as con:
                rs = con.execute("SELECT "
                "IF(((SELECT DISTINCT "
                "T1.name "
                "FROM "
                "(SELECT DISTINCT "
                "S1.bar_id, "
                "CONCAT(S1.name, ' & ', S2.name) AS 'name', "
                "IF(S1.price < S2.price, '<', '>') AS 'Relation' "
                "FROM "
                "sells S1 "
                "INNER JOIN sells S2 ON S1.bar_id = S2.bar_id "
                "WHERE "
                "S1.name != S2.name AND S1.name < S2.name "
                "AND S1.name NOT IN (SELECT " 
                "item.name "
                "FROM "
                "item "
                "WHERE "
                "manf IS NULL) "
                "AND S2.name NOT IN (SELECT " 
                "item.name "
                "FROM "
                "item "
                "WHERE "
                "manf IS NULL)) T1, "
                "(SELECT DISTINCT "
                "S1.bar_id, "
                "CONCAT(S1.name, ' & ', S2.name) AS 'name', "
                "IF(S1.price < S2.price, '<', '>') AS 'Relation' "
                "FROM "
                "sells S1 "
                "INNER JOIN sells S2 ON S1.bar_id = S2.bar_id "
                "WHERE "
                "S1.name != S2.name AND S1.name < S2.name "
                "AND S1.name NOT IN (SELECT " 
                "item.name "
                "FROM "
                "item "
                "WHERE "
                "manf IS NULL) "
                "AND S2.name NOT IN (SELECT " 
                "item.name "
                "FROM "
                "item "
                "WHERE "
                "manf IS NULL)) T2 "
                "WHERE "
                "T1.name = T2.name "
                "AND T1.Relation != T2.Relation)) IS NULL, "
                "TRUE, "
                "FALSE) as verify")

                results = [dict(row) for row in rs]
                
                return results

def delete_frequent_violation():
        with engine.connect() as con:
                rs = con.execute("SELECT frequents.drinker_id, frequents.bar_id FROM frequents, drinker, bar "
                "WHERE frequents.drinker_id = drinker.drinker_id AND frequents.bar_id = bar.bar_id "
                "AND drinker.state <> bar.state")

                results = [dict(row) for row in rs]

                drinkerID = results[0]['drinker_id']
                barID = results[0]['bar_id']

                rs = con.execute("DELETE FROM frequents "
                "WHERE drinker_id = '"+str(drinkerID)+"\' AND bar_id = '"+str(barID)+"\'")
                


                return results




