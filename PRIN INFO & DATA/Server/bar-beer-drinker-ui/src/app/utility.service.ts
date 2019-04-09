import { Injectable } from '@angular/core';

import { Location } from '@angular/common';

declare const Highcharts: any;

@Injectable({
  providedIn: 'root'
})
export class UtilityService {
  constructor(private location: Location) {}

  cancel() {
    this.location.back(); // <-- go back to previous location on cancel
  }

  renderChart(array: string[], count: number[], graph_id: string, title: string, yText: string, xText: string, chartType: string) {
    Highcharts.chart(graph_id, {
      chart: {
        type: chartType
      },
      title: {
        text: title
      },
      xAxis: {
        categories: array,
        title: {
          text: xText
        }
      },
      yAxis: {
        min: 0,
        title: {
          text: yText
        },
        labels: {
          overflow: 'justify'
        }
      },
      plotOptions: {
        bar: {
          dataLabels: {
            enabled: true
          }
        }
      },
      legend: {
        enabled: false
      },
      credits: {
        enabled: false
      },
      series: [
        {
          data: count
        }
      ]
    });
  }
}
