import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';

export interface Validity {
  verify: boolean;
}

@Injectable({
  providedIn: 'root'
})
export class VerifyService {
  constructor(public http: HttpClient) {}

  verify_frequents() {
    return this.http.get<Validity>('/api/verify/frequents');
  }

  verify_operatinghours() {
    return this.http.get<Validity>('/api/verify/operating_hours');
  }

  verify_beer() {
    return this.http.get<Validity>('/api/verify/beer_constraint');
  }
}
