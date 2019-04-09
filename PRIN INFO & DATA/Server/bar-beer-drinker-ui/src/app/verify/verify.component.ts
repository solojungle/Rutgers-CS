import { Component, OnInit } from '@angular/core';
import { VerifyService, Validity } from '../verify.service';

@Component({
  selector: 'app-verify',
  templateUrl: './verify.component.html',
  styleUrls: ['./verify.component.scss']
})
export class VerifyComponent implements OnInit {
  frequents: boolean;
  operating: boolean;
  beer: boolean;

  constructor(private verifyService: VerifyService) {}

  ngOnInit() {
    this.verify_frequents();
    this.verify_operatinghours();
    this.verify_beer();
  }

  verify_frequents() {
    this.verifyService.verify_frequents().subscribe(data => {
      if (data[0].verify == 1) {
        this.frequents = true;
      } else {
        this.frequents = false;
      }
    });
  }

  verify_operatinghours() {
    this.verifyService.verify_operatinghours().subscribe(data => {
      if (data[0].verify == 1) {
        this.operating = true;
      } else {
        this.operating = false;
      }
    });
  }

  verify_beer() {
    this.verifyService.verify_beer().subscribe(data => {
      if (data[0].verify == 1) {
        this.beer = true;
      } else {
        this.beer = false;
      }
    });
  }
}
