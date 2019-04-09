import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';
import { NgForm } from '@angular/forms';

@Injectable({
  providedIn: 'root'
})
export class SqlService {

  constructor(
    private http: HttpClient
  ) { }

    sql_box(form: NgForm) {
      return this.http.get('/api/sql_box/' + form.value.query);
    }

}
