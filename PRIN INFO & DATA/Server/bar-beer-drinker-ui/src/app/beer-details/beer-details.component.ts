import { Component, OnInit } from '@angular/core';
import { HttpResponse } from '@angular/common/http';
import { ActivatedRoute } from '@angular/router';
import { BeersService, BestBeer, BeerFans, BigConsumer, BeerTime } from '../beers.service';
import { UtilityService } from '../utility.service';

@Component({
  selector: 'app-beer-details',
  templateUrl: './beer-details.component.html',
  styleUrls: ['./beer-details.component.scss']
})
export class BeerDetailsComponent implements OnInit {
  beer_id: string;
  beer_details: BestBeer;
  beer_fans: BeerFans[];
  beer_consumers: BigConsumer[];
  beer_times: BeerTime[];

  constructor(private beerService: BeersService, private utilityService: UtilityService, private route: ActivatedRoute) {
    route.paramMap.subscribe(paramMap => {
      this.beer_id = paramMap.get('id');
      beerService.get_beers_bestsellers(this.beer_id).subscribe(
        data => {
          this.beer_details = data[0];
        },
        (error: HttpResponse<any>) => {
          if (error.status === 404) {
            alert('Beer not found');
          } else {
            console.error(error.status + ' - ' + error.body);
            alert('An error occurred on the server, or that beer does not exist.');
          }
        }
      );
    });
  }

  cancel() {
    this.utilityService.cancel();
  }

  ngOnInit() {
    this.get_beer_fans();
    this.get_biggest_consumers();
    this.get_time_beer_sells();
  }

  get_beer_fans() {
    this.beerService.get_beer_fans(this.beer_id).subscribe(
      data => {
        this.beer_fans = data;
        const array = [];
        const count = [];

        let i = 0;
        data.forEach(drinker => {
          array.push(this.beer_fans[i].name);
          count.push(this.beer_fans[i].num_of_sales);
          i++;
        });
        this.utilityService.renderChart(array, count, 'beer-fan-graph', 'Where Beer Sells Most', '# Of Sales', 'Name Of Bar', 'column');
      },
      error => {
        if (!this.beer_details) {
          alert('Beer does not have a biggest fan.');
        }
      }
    );
  }

  get_biggest_consumers() {
    this.beerService.get_biggest_consumers(this.beer_id).subscribe(
      data => {
        this.beer_consumers = data;
        const array = [];
        const count = [];

        let i = 0;
        data.forEach(drinker => {
          array.push(this.beer_consumers[i].first + ' ' + this.beer_consumers[i].last);
          count.push(this.beer_consumers[i].num_of_orders);
          i++;
        });
        this.utilityService.renderChart(array, count, 'beer-consumer-graph', 'Biggest Consumer Of Beer', '# Of Orders', 'Name Of Drinker', 'column');
      },
      error => {
        if (this.beer_details) {
          alert('This beer is not sold anywhere, graphs were not generated.');
        } else {
          alert('Beer does not have a biggest consumer.');
        }
      }
    );
  }

  get_time_beer_sells() {
    this.beerService.get_time_beer_sells(this.beer_id).subscribe(
      data => {
        this.beer_times = data;
        const array = [];
        const count = [];

        let i = 0;
        data.forEach(e => {
          array.push(this.convertTo12(this.beer_times[i].hour));
          count.push(this.beer_times[i].num_of_orders);
          i++;
        });
        this.utilityService.renderChart(array, count, 'beer-times-graph', 'Time Distribution Of Sales', '# Of Sales', 'Time Of Day', 'column');
      },
      error => {
        if (!this.beer_details) {
          alert('Could not get beer times.');
        }
      }
    );
  }

  convertTo12(hour) {
    hour = parseInt(hour, 10);
    const suffix = hour >= 12 ? 'PM' : 'AM';
    hour = hour > 12 ? hour - 12 : hour;
    hour = hour === 0 ? 12 : hour;
    return hour + ' ' + suffix;
  }
}
