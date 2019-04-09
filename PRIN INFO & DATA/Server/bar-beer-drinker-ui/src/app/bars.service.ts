import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';

export interface Bar {
  name: string;
  addr: string;
  city: string;
  state: string;
  zip: string;
  phone: string;
  open: string;
  close: string;
  bar_id: number;
}

export interface TopDrinker {
  first: string;
  last: string;
  sum: number;
}

export interface PopularBeer {
  'count(item)': number;
  item: string;
}

export interface TopManf {
  manf: string;
  num_beers_sold_by_manf: number;
}

export interface BillTime {
  hour: string;
  num_of_orders: number;
}

export interface BillDays {
  day_of_week: number;
  num_of_orders: number;
}

@Injectable({
  providedIn: 'root'
})
export class BarsService {
  constructor(public http: HttpClient) {}

  getBarsGeneral() {
    return this.http.get<Bar[]>('/api/bar');
  }

  getBar(barID: string) {
    return this.http.get<Bar>('/api/bar/' + barID);
  }

  getTopDrinkers(barID: string) {
    return this.http.get<TopDrinker[]>('/api/bar/top_drinkers/' + barID);
  }

  getPopularBeers(barID: string) {
    return this.http.get<PopularBeer[]>('/api/bar/popular_beer/' + barID);
  }

  get_top_manf(barID: string) {
    return this.http.get<TopManf[]>('/api/bar/top_manf/' + barID);
  }

  get_bill_times(bar_id: string) {
    return this.http.get<BillTime[]>('/api/bar/bill_times/' + bar_id);
  }

  bill_time_dayofweek(bar_id: string) {
    return this.http.get<BillDays[]>('/api/bar/busiest_dayofweek/' + bar_id);
  }
}
