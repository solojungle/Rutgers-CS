import { Component, OnInit } from '@angular/core';
import { UtilityService } from '../utility.service';
import { DrinkersService, Order } from '../drinkers.service';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-bill-details',
  templateUrl: './bill-details.component.html',
  styleUrls: ['./bill-details.component.scss']
})
export class BillDetailsComponent implements OnInit {
  bill_id: string;
  orders: Order[];

  constructor(private utilityService: UtilityService, private drinkerService: DrinkersService, public route: ActivatedRoute) {
    route.paramMap.subscribe(paramMap => {
      this.bill_id = paramMap.get('id');
    });
  }

  cancel() {
    this.utilityService.cancel();
  }

  ngOnInit() {
    this.get_orders_for_bill();
  }

  get_orders_for_bill() {
    this.drinkerService.get_orders_for_bill(this.bill_id).subscribe(
      data => {
        this.orders = data;
        console.log(this.orders);
      },
      error => {
        alert('Could not find orders for bill.');
      }
    );
  }
}
