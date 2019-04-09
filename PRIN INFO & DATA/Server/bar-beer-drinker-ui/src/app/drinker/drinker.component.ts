import { Component, OnInit } from '@angular/core';

import { DrinkersService, Drinker } from '../drinkers.service';

@Component({
  selector: 'app-drinker',
  templateUrl: './drinker.component.html',
  styleUrls: ['./drinker.component.scss']
})
export class DrinkerComponent implements OnInit {
    drinkers: Drinker[];
  constructor(public drinkerService: DrinkersService) {}
  ngOnInit() {
    this.get_drinkers();
  }
  get_drinkers() {
      this.drinkerService.get_drinkers().subscribe(data => {
        this.drinkers = data;
      }, error => {
        alert('Could not retrieve a list of drinkers')
      });
  }
}
