from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request
import json

from BarBeerDrinker import database

app = Flask(__name__)

#CATEGORY: OTHER

@app.route('/')
def hello_world():
    return 'Welcome to the API.'

###################################################

#CATEGORY: BAR

@app.route('/api/bar', methods=["GET"]) #GOOD!!  
def get_bars_general():                 
    try:                                
        return jsonify(database.get_bars_general())
    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/<barID>', methods=["GET"])  #GOOD!  #NEED TO ADD REST OF BAR DATA
def get_bars(barID):                                
    try:                                         
        if barID is None:                       
            raise ValueError("Bar was not specified.")

        results = jsonify(database.get_bars(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/popular_beer/<barID>', methods=["GET"]) #GOOD!
def get_popular_beers(barID):                           #IT GETS THE AMOUNT OF TIMES THE BEER WAS ORDERED
    try:                                                #DOES NOT INCLUDE THE QUANTITY WHEN CALCULATING POPULARITY
        if barID is None:                               #NOT SURE IF THIS IS OKAY?? JEFF SAID WE ARE GOOD!!
            raise ValueError("Bar was not specified.")

        results = jsonify(database.get_popular_beers(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/top_manf/<barID>', methods=["GET"])  #GOOD!!
def get_top_manf(barID):
    try:
        if barID is None:                               
            raise ValueError("Bar was not specified.")

        results = jsonify(database.get_top_manf(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/top_drinkers/<barID>', methods=["GET"])   #GOOD!
def get_top_drinkers(barID):                                  #NEED TO CHECK SQL QUERY ADDS CORRECTLY IF THE
    try:                                                      #DRINKER HAS MORE THAN ONE BILL AT A BAR
        if barID is None:
            raise ValueError("Bar was not specified")

        results = jsonify(database.get_bars(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')
        if barID is None:
            raise ValueError("Bar ID was not specified")

        results = jsonify(database.get_top_drinkers(barID))
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/bill_times/<barID>', methods=["GET"])
def get_bill_times(barID):                   #NOTE: USE THIS TO GET THE BUSIEST PERIODS OF THE DAY FOR A BAR!!   
    try:                                     # WHEN DOING THE GRAPH DO IT BY THE HOUR AND TRANSLATE IT INTO THE 12 HOUR CLOCK                 
        if barID is None:
            raise ValueError("Bar was not specified")

        results = jsonify(database.get_bill_times(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')

        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/bar/busiest_dayofweek/<barID>', methods=["GET"])  #GOOD!!! ****NOTE: day of week is in a number format.
def bill_time_dayofweek(barID):                   # Must translate it as shown, 1 = Sunday, 2 = Monday,  7 = Saturday
    try:                                                  
        if barID is None:
            raise ValueError("Bar was not specified")

        results = jsonify(database.busiest_dayofweek(barID))
        if results.get_json() == []:
            raise ValueError('Bar does not exist.')
      
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


#########################################################

#CATEGORY: BEER

@app.route('/api/beer', methods=["GET"]) #GOOD!!
def get_beers():
    try:
        return jsonify(database.get_beers())
    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


@app.route('/api/beer/<name>', methods=["GET"])  #GOOD!!
def get_beers_bestsellers(name):
    try:
        if name is None:
            raise ValueError("Beer was not specified.")

        results = jsonify(database.get_beer(name))
        if results.get_json() == []:
            raise ValueError('Beer does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/beer/popular/<name>', methods=["GET"]) # GOOD!
def get_beer_fans(name):                                # DO YOU NEED TO FACTOR IN QUANTITY PER ORDER WHEN FIGURING OUT POPULARITY?
    try:                                                # JEFF SAID WE ARE GOOD!!
        if name is None:
            raise ValueError("Beer was not specified.")

        results = jsonify(database.get_beer_popularity(name))
        if results.get_json() == []:
            raise ValueError('Beer does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/beer/biggest_consumers/<name>', methods=["GET"]) # GOOD!!!
def get_biggest_consumers(name):                 # NOTE: Beer named '16' is not sold or ordered by anyone and 
    try:                                         # it says that 'beer does not exist'. It does exist!!       
        if name is None:
            raise ValueError("Beer was not specified.")

        results = jsonify(database.get_biggest_consumer(name))
        if results.get_json() == []:
            raise ValueError('Beer does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

#Use this to graph time distribution when this beer sells the most
@app.route('/api/beer/times_beer_sells/<name>', methods=["GET"])  # GOOD!!!
def get_time_beer_sells(name):                                    # NOTE: USE THE HOUR THE BEER WAS SOLD TO CREATE BAR GRAPH
    try:                                                          # HOUR IS IN 24 HOUR CLOCK, TRANSFER IT TO 12 HOUR CLOCK
        if name is None:
            raise ValueError("Beer was not specified.")

        results = jsonify(database.get_times_beer_sells_most(name))
        if results.get_json() == []:
            raise ValueError('Beer does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


#################################################################################

#CATEGORY: DRINKER

@app.route('/api/drinker', methods=["GET"])  # GOOD!
def get_drinkers():
    try:
        return jsonify(database.get_drinkers())
    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/drinker/<drinkerID>', methods=["GET"]) #GOOD!!
def get_drinker(drinkerID):
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_drinker(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


@app.route('/api/drinker/bill/<drinkerID>', methods=["GET"])  # GOOD!!
def get_drinker_bill(drinkerID):                              #NOTE: USE THIS DATA TO CREATE TABLE FOR ALL OF THE DRINKER'S BILLS
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_drinker_bills(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/drinker/beers_ordered_most/<drinkerID>', methods=["GET"]) #GOOD!!!!
def get_beers_ordered_most(drinkerID):
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_beers_ordered_most(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

#SPENDING BY DATES IN DIFFERENT BARS #############FIXED IT!! IT works the way we want now!!!
@app.route('/api/drinker/spending_dates/<drinkerID>', methods=["GET"]) # GOOD!!
def get_spending_bydates(drinkerID):
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_spending_bydate(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

#SPENDING BY MONTHS IN DIFFERENT BARS  #############FIXED IT!! IT works the way we want now!!!
@app.route('/api/drinker/spending_month/<drinkerID>', methods=["GET"])  #GOOD!!! 
def get_spending_bymonth(drinkerID):                                      #NOTE: Month comes back in number format {1=Janurary, 2=Feb, 12=Dec}
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_spending_bymonth(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

#SPENDING BY MONTHS IN DIFFERENT BARS  #############FIXED IT!! IT works the way we want now!!!
@app.route('/api/drinker/spending_week/<drinkerID>', methods=["GET"])  #GOOD!!! 
def get_spending_byweek(drinkerID):                                      #NOTE: Start it by Week 0, week 1,  ,week 53
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_spending_byweek(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/drinker/bars_drinker_ordered_from/<drinkerID>') 
def get_allbars_drinker_orders(drinkerID):
    try:
        if drinkerID is None:
            raise ValueError("Drinker was not specified.")

        results = jsonify(database.get_allbars_drinkerorders_from(drinkerID))
        if results.get_json() == []:
            raise ValueError('Drinker does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/drinker/insert_drinker/<first>/<last>/<addr>/<city>/<state>/<zip>/<phone>', methods=["POST"])
def insert_drinker(first, last, addr, city, state, zip, phone):
    try:

        isInserted = database.insert_drinker(first,last,addr,city,state,zip,phone)   

        if isInserted is False:
            raise ValueError('Duplicate Drinker')

        return "[INSERT : true]"
    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


#################################################################################

#CATEGORY: ORDERS

@app.route('/api/orders/<billID>', methods=["GET"])   #GOOD!!!
def get_orders_forbill(billID):      #NOTE: USE THIS TO DISPLAY ORDERS WHEN BILL IS CLICKED THE IN TABLE ON THE DRINKER'S PAGE
    try:
        if billID is None:
            raise ValueError("Bill was not specified.")

        results = jsonify(database.get_orders_forbill(billID))
        if results.get_json() == []:
            raise ValueError('Bill does not exist.')
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/insert_drinkerquery/<query>', methods=["GET"])
def insert_query(query):
    try:
        if query is None:
            raise ValueError("No Query")

        isInserted = database.insert_drinkerquery(query)

        frequentVerify = database.verify_frequents()

        if(frequentVerify[0]['verify'] == 0):
            database.delete_frequent_violation()
           
            return json.dumps([{"INSERT" : "Insert Failed. Violates Frequents Constraint."}])

    
        return json.dumps([{"INSERT" : "True"}])

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/sql_box/<query>')
def sql_box(query):
    try:
        if query is None:
            raise ValueError("No Query")

        results = jsonify(database.sql_box(query))
       
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)


###############################################################################################

#SQL Verification Query

@app.route('/api/verify/frequents')
def verify_frequents():

    try:
        results = jsonify(database.verify_frequents())
       
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/verify/operating_hours')
def verify_operatinghours():
    try:
        results = jsonify(database.verify_operating_hours())
       
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)

@app.route('/api/verify/beer_constraint')
def verify_beer():
    try:

        results = jsonify(database.verify_beer_constraint())
       
        return results

    except ValueError as e:
        return make_response(str(e), 400)
    except Exception as e:
        return make_response(str(e), 500)    


