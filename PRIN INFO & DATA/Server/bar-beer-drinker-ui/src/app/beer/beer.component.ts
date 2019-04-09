import { Component, OnInit } from '@angular/core';

import { BeersService, Beer } from '../beers.service';

@Component({
  selector: 'app-beer',
  templateUrl: './beer.component.html',
  styleUrls: ['./beer.component.scss']
})
export class BeerComponent implements OnInit {
    beers: Beer[];
    constructor(public beerService: BeersService) {}
    ngOnInit() {
        this.get_beers();
    }
    get_beers() {
        this.beerService.get_beers().subscribe(data => {
            this.beers = data;
        }, error => {
            alert('Could not retrieve a list of beers')
        });
    }
}
