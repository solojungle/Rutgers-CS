import { Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';
import { NgForm } from '@angular/forms';

@Injectable({
  providedIn: 'root'
})
export class ModsService {

  constructor(
    private http: HttpClient
  ) { }

    post_insert_drinker(form: NgForm) {
      return this.http.get('/api/insert_drinkerquery/' + form.value.query);
    }

}
