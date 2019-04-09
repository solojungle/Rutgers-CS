import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';

export interface Beer {
  name: string;
  manf: string;
}

export interface BestBeer {
  category: string;
  manf: string;
  name: string;
}

export interface BeerFans {
  name: string;
  num_of_sales: number;
}

export interface BigConsumer {
  first: string;
  last: string;
  num_of_orders: number;
}

export interface BeerTime {
  hour: string;
  num_of_orders: string;
}

@Injectable({
  providedIn: 'root'
})
export class BeersService {
  constructor(public http: HttpClient) {}

  get_beers() {
    return this.http.get<Beer[]>('/api/beer');
  }

  get_beers_bestsellers(beer_id: string) {
    return this.http.get<BestBeer[]>('/api/beer/' + beer_id);
  }

  get_beer_fans(beer_id: string) {
    return this.http.get<BeerFans[]>('/api/beer/popular/' + beer_id);
  }

  get_biggest_consumers(beer_id: string) {
    return this.http.get<BigConsumer[]>('/api/beer/biggest_consumers/' + beer_id);
  }

  get_time_beer_sells(beer_id: string) {
    return this.http.get<BeerTime[]>('/api/beer/times_beer_sells/' + beer_id);
  }
}
