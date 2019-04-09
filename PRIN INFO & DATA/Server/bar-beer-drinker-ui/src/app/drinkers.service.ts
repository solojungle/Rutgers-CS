import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';

export interface Drinker {
  drinker_id: number;
  first: string;
  last: string;
  addr: string;
  city: string;
  state: string;
  zip: string;
  phone: string;
}

export interface Bill {
  bill_id: string;
  date: string;
  grand_total: string;
  name: string;
  tax: string;
  time: string;
  tip: string;
  total: string;
}

export interface MostOrderedBeer {
  item: string;
  num_of_orders: number;
}

export interface Order {
  bill_id: string;
  item: string;
  order_id: string;
  price: string;
  qty: string;
}

export interface SpendingDate {
  date: string;
  spending_during_date: string;
}

export interface SpendingWeek {
  week_num: string;
  spending_during_week: string;
}

export interface SpendingMonth {
  month: number;
  spending_during_month: string;
}

@Injectable({
  providedIn: 'root'
})
export class DrinkersService {
  constructor(public http: HttpClient) {}

  get_drinkers() {
    return this.http.get<Drinker[]>('/api/drinker');
  }

  get_drinker(drinker_id: string) {
    return this.http.get<Drinker[]>('/api/drinker/' + drinker_id);
  }

  get_beers_ordered_most(drinker_id: string) {
    return this.http.get<MostOrderedBeer[]>('/api/drinker/beers_ordered_most/' + drinker_id);
  }

  get_drinker_bill(drinker_id: string) {
    return this.http.get<Bill[]>('/api/drinker/bill/' + drinker_id);
  }

  get_orders_for_bill(bill_id: string) {
    return this.http.get<Order[]>('/api/orders/' + bill_id);
  }

  get_spending_bydates(drinker_id: string) {
    return this.http.get<SpendingDate[]>('/api/drinker/spending_dates/' + drinker_id);
  }

  get_spending_byweek(drinker_id: string) {
    return this.http.get<SpendingWeek[]>('/api/drinker/spending_week/' + drinker_id);
  }

  get_spending_bymonth(drinker_id: string) {
    return this.http.get<SpendingMonth[]>('/api/drinker/spending_month/' + drinker_id);
  }
}
