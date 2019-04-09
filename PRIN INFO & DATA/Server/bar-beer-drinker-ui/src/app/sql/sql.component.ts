import { Component, OnInit } from '@angular/core';

import { SqlService } from '../sql.service';
import { HttpClient } from '@angular/common/http';
import { NgForm } from '@angular/forms';

@Component({
  selector: 'app-sql',
  templateUrl: './sql.component.html',
  styleUrls: ['./sql.component.scss']
})
export class SqlComponent implements OnInit {

  constructor(public sqlService: SqlService, private http: HttpClient) {}
  dataSet: object;
  show: boolean;
  keys: Array<string>;

  submitted = false;

  ngOnInit() {}
  onSubmit(form: NgForm) {
    this.sqlService.sql_box(form).subscribe(
      data => {
        this.dataSet = data;
        this.keys = Object.keys(this.dataSet[0]);
        this.show = true;
      },
      error => {
        console.log(error);
        if (error.status === 200) {
          alert('Success');
        } else {
          alert(error.error);
        }
      }
    );
  }
}
