import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { HttpResponse } from '@angular/common/http';
import { DrinkersService, Drinker, MostOrderedBeer, Bill, SpendingDate, SpendingWeek, SpendingMonth } from '../drinkers.service';
import { UtilityService } from '../utility.service';

@Component({
  selector: 'app-drinker-details',
  templateUrl: './drinker-details.component.html',
  styleUrls: ['./drinker-details.component.scss']
})
export class DrinkerDetailsComponent implements OnInit {
  drinker_id: string;
  drinker_details: Drinker;
  bill_details: Bill[];
  beers_ordered_most: MostOrderedBeer[];
  spending_date: SpendingDate[];
  spending_week: SpendingWeek[];
  spending_month: SpendingMonth[];

  constructor(private drinkerService: DrinkersService, private utilityService: UtilityService, private route: ActivatedRoute) {
    route.paramMap.subscribe(paramMap => {
      this.drinker_id = paramMap.get('id');
      drinkerService.get_drinker(this.drinker_id).subscribe(
        data => {
          this.drinker_details = data[0];
        },
        (error: HttpResponse<any>) => {
          if (error.status === 404) {
            alert('Bar not found');
          } else {
            console.error(error.status + ' - ' + error.body);
            alert('An error occurred on the server.');
          }
        }
      );
    });
  }

  cancel() {
    this.utilityService.cancel();
  }

  ngOnInit() {
    this.get_beers_ordered_most();
    this.get_spending_bydates();
    this.get_spending_byweek();
    this.get_spending_bymonth();
    this.get_drinker_bill();
  }

  get_beers_ordered_most() {
    this.drinkerService.get_beers_ordered_most(this.drinker_id).subscribe(
      data => {
        this.beers_ordered_most = data;
        const items = [];
        const count = [];
        let i = 0;
        data.forEach(drinker => {
          items.push(this.beers_ordered_most[i].item);
          count.push(this.beers_ordered_most[i].num_of_orders);
          i++;
        });
        this.utilityService.renderChart(items, count, 'most-ordered-beer-graph', 'Most Ordered Beers', '# Of Orders', 'Name Of Beer', 'column');
      },
      error => {
        alert('Could not find beers ordered most.');
      }
    );
  }

  get_drinker_bill() {
    this.drinkerService.get_drinker_bill(this.drinker_id).subscribe(
      data => {
        this.bill_details = data;
        let i = 0;
        data.forEach(e => {
          this.bill_details[i].time = this.convertTo12(this.bill_details[i].time.split(':'));
          i++;
        });
      },
      error => {
        alert('Could not find drinker bill.');
      }
    );
  }

  get_spending_bydates() {
    this.drinkerService.get_spending_bydates(this.drinker_id).subscribe(
      data => {
        this.spending_date = data;
        const array = [];
        const count = [];
        let i = 0;
        data.forEach(e => {
          array.push(this.spending_date[i].date);
          count.push(this.spending_date[i].spending_during_date);
          i++;
        });
        this.utilityService.renderChart(array, count, 'spending-date-graph', 'Bar Spending Per Date', 'Spending During Date', 'Dates', 'column');
      },
      error => {
        alert('Could not find spending by dates.');
      }
    );
  }

  get_spending_byweek() {
    this.drinkerService.get_spending_byweek(this.drinker_id).subscribe(
      data => {
        this.spending_week = data;
        const array = [];
        const count = [];
        let i = 0;
        data.forEach(e => {
          array.push('Week' + ' ' + this.spending_week[i].week_num);
          count.push(this.spending_week[i].spending_during_week);
          i++;
        });
        this.utilityService.renderChart(array, count, 'spending-week-graph', 'Bar Spending Per Week', 'Spending During Week', 'Week Number', 'column');
      },
      error => {
        alert('Could not find spending by weeks.');
      }
    );
  }

  get_spending_bymonth() {
    this.drinkerService.get_spending_bymonth(this.drinker_id).subscribe(
      data => {
        this.spending_month = data;
        const array = [];
        const count = [];
        let i = 0;
        data.forEach(e => {
          switch (this.spending_month[i].month) {
            case 1:
              array.push('Jan');
              break;
            case 2:
              array.push('Feb');
              break;
            case 3:
              array.push('Mar');
              break;
            case 4:
              array.push('Apr');
              break;
            case 5:
              array.push('May');
              break;
            case 6:
              array.push('Jun');
              break;
            case 7:
              array.push('Jul');
              break;
            case 8:
              array.push('Aug');
              break;
            case 9:
              array.push('Sep');
              break;
            case 10:
              array.push('Oct');
              break;
            case 11:
              array.push('Nov');
              break;
            case 12:
              array.push('Dec');
              break;
          }
          count.push(this.spending_month[i].spending_during_month);
          i++;
        });
        this.utilityService.renderChart(array, count, 'spending-month-graph', 'Bar Spending Per Month', 'Spending During Month', 'Month', 'column');
      },
      error => {
        alert('Could not find spending by months.');
      }
    );
  }

  convertTo12(array) {
    array[0] = parseInt(array[0], 10);
    const suffix = array[0] >= 12 ? 'PM' : 'AM';
    array[0] = array[0] > 12 ? array[0] - 12 : array[0];
    array[0] = array[0] === 0 ? 12 : array[0];
    return array[0] + ':' + array[1] + ' ' + suffix;
  }
}
