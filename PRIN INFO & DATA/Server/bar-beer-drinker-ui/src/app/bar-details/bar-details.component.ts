import { Component, OnInit } from '@angular/core';
import { HttpResponse } from '@angular/common/http';
import { ActivatedRoute } from '@angular/router';
import { BarsService, Bar, TopDrinker, PopularBeer, TopManf, BillDays, BillTime } from '../bars.service';
import { UtilityService } from '../utility.service';

@Component({
  selector: 'app-bar-details',
  templateUrl: './bar-details.component.html',
  styleUrls: ['./bar-details.component.scss']
})
export class BarDetailsComponent implements OnInit {
  bar_id: string;
  drinkers: TopDrinker[];
  popular_beers: PopularBeer[];
  top_manf: TopManf[];
  bill_days: BillDays[];
  bill_times: BillTime[];
  barDetails: Bar;
  open_time: string;
  close_time: string;

  constructor(private barService: BarsService, private utilityService: UtilityService, private route: ActivatedRoute) {
    route.paramMap.subscribe(paramMap => {
      this.bar_id = paramMap.get('id');
      barService.getBar(this.bar_id).subscribe(
        data => {
          this.barDetails = data[0];

          this.open_time = convertTo12(this.barDetails.open.split(':'));
          this.close_time = convertTo12(this.barDetails.close.split(':'));

          function convertTo12(array) {
            array[0] = parseInt(array[0], 10);
            const suffix = array[0] >= 12 ? 'PM' : 'AM';
            array[0] = array[0] > 12 ? array[0] - 12 : array[0];
            array[0] = array[0] === 0 ? 12 : array[0];
            return array[0] + ':' + array[1] + ' ' + suffix;
          }
        },
        (error: HttpResponse<any>) => {
          if (error.status === 404) {
            alert('Bar not found');
          } else {
            console.error(error.status + ' - ' + error.body);
            alert('An error occurred on the server, or that bar does not exist.');
          }
        }
      );
    });
  }

  cancel() {
    this.utilityService.cancel();
  }

  ngOnInit() {
    this.get_top_drinkers();
    this.get_popular_beers();
    this.get_top_manf();
    this.get_bill_times();
    this.bill_time_dayofweek();
  }

  get_top_drinkers() {
    this.barService.getTopDrinkers(this.bar_id).subscribe(
      data => {
        this.drinkers = data;
        const topDrinkers = [];
        const count = [];

        let i = 0;
        data.forEach(drinker => {
          topDrinkers.push(this.drinkers[i].first + ' ' + this.drinkers[i].last);
          count.push(this.drinkers[i].sum);
          i++;
        });
        this.utilityService.renderChart(topDrinkers, count, 'top-drinkers-graph', 'Top Drinkers', 'Count Of Expenditures', 'Name Of Drinker', 'column');
      },
      error => {
        alert('Could not find drinker.');
      }
    );
  }

  get_popular_beers() {
    this.barService.getPopularBeers(this.bar_id).subscribe(
      data => {
        this.popular_beers = data;
        const popularBeers = [];
        const count = [];

        let i = 0;
        data.forEach(drinker => {
          popularBeers.push(this.popular_beers[i].item);
          count.push(this.popular_beers[i]['count(item)']);
          i++;
        });
        this.utilityService.renderChart(popularBeers, count, 'popular-beers-graph', 'Most Popular Beers', '# Of Orders', 'Name Of Beer', 'column');
      },
      error => {
        alert('Could not find popular beers.');
      }
    );
  }

  get_top_manf() {
    this.barService.get_top_manf(this.bar_id).subscribe(
      data => {
        this.top_manf = data;
        const manfArr = [];
        const count = [];

        let i = 0;
        data.forEach(drinker => {
          manfArr.push(this.top_manf[i].manf);
          count.push(this.top_manf[i].num_beers_sold_by_manf);
          i++;
        });
        this.utilityService.renderChart(manfArr, count, 'top-manf-graph', 'Top Manufacturers', '# Of Beers Sold By Manf', 'Name Of Manf.', 'column');
      },
      error => {
        alert('Could not find top manf.');
      }
    );
  }

  get_bill_times() {
    this.barService.get_bill_times(this.bar_id).subscribe(
      data => {
        this.bill_times = data;
        const array = [];
        const count = [];

        let i = 0;
        data.forEach(e => {
          count.push(this.bill_times[i].num_of_orders);
          let temp = parseInt(this.bill_times[i].hour, 10);
          const suffix = temp >= 12 ? 'PM' : 'AM';
          temp = temp > 12 ? temp - 12 : temp;
          temp = temp === 0 ? 12 : temp;
          array.push(temp + ' ' + suffix);
          i++;
        });
        this.utilityService.renderChart(array, count, 'day-dist-graph', 'Busiest Hours Of The Day', '# Of Orders', 'Hour Of The Day', 'column');
      },
      error => {
        alert('Could not find bill times.');
      }
    );
  }

  bill_time_dayofweek() {
    this.barService.bill_time_dayofweek(this.bar_id).subscribe(
      data => {
        this.bill_days = data;
        const array = [];
        const count = [];

        let i = 0;
        data.forEach(e => {
          switch (this.bill_days[i].day_of_week) {
            case 1:
              array.push('Sunday');
              break;
            case 2:
              array.push('Monday');
              break;
            case 3:
              array.push('Tuesday');
              break;
            case 4:
              array.push('Wednesday');
              break;
            case 5:
              array.push('Thursday');
              break;
            case 6:
              array.push('Friday');
              break;
            case 7:
              array.push('Saturday');
              break;
          }
          count.push(this.bill_days[i].num_of_orders);
          i++;
        });
        this.utilityService.renderChart(array, count, 'week-dist-graph', 'Busiest Days Of The Week', '# Of Orders', 'Day Of The Week', 'column');
      },
      error => {
        alert('Could not find bill times.');
      }
    );
  }
}
