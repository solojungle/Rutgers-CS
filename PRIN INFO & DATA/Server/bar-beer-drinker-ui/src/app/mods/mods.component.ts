import { Component, OnInit } from '@angular/core';

import { ModsService } from '../mods.service';
import { HttpClient } from '@angular/common/http';
import { NgForm } from '@angular/forms';

@Component({
  selector: 'app-mods',
  templateUrl: './mods.component.html',
  styleUrls: ['./mods.component.scss']
})
export class ModsComponent implements OnInit {
  constructor(public modService: ModsService, private http: HttpClient) {}

  ngOnInit() {}

  submitted = false;
  onSubmit(form: NgForm) {
    this.modService.post_insert_drinker(form).subscribe(
      data => {
        alert(data[0].INSERT);
      },
      error => {
        if (error.status === 200) {
          alert('Success');
        } else {
          alert(error.error);
        }
      }
    );
  }
}
