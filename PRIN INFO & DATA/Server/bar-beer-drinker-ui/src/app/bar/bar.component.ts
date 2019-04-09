import { Component, OnInit } from '@angular/core';

import { BarsService, Bar } from '../bars.service';

@Component({
  selector: 'app-bar',
  templateUrl: './bar.component.html',
  styleUrls: ['./bar.component.scss']
})
export class BarComponent implements OnInit {
	bars: Bar[];
	constructor(public barService: BarsService) {}
	ngOnInit() {
		this.getBarsGeneral();
	}
	getBarsGeneral() {
		this.barService.getBarsGeneral().subscribe(data => {
			this.bars = data;
		}, error => {
			alert('Could not retrieve a list of bars');
		});
	}
}
