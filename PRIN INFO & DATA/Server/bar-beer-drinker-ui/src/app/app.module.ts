import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { HttpClientModule, HttpClient } from '@angular/common/http';
import { FormsModule } from '@angular/forms';
import { BarComponent } from './bar/bar.component';
import { BeerComponent } from './beer/beer.component';
import { DrinkerComponent } from './drinker/drinker.component';
import { FilterPipe } from './filter.pipe';
import { TableModule } from 'primeng/table';
import { DropdownModule } from 'primeng/dropdown';
import { BarDetailsComponent } from './bar-details/bar-details.component';
import { DrinkerDetailsComponent } from './drinker-details/drinker-details.component';
import { BeerDetailsComponent } from './beer-details/beer-details.component';
import { ModsComponent } from './mods/mods.component';
import { SqlComponent } from './sql/sql.component';
import { SqlPipe } from './sql.pipe';
import { BillDetailsComponent } from './bill-details/bill-details.component';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import { VerifyComponent } from './verify/verify.component';

@NgModule({
  declarations: [
    AppComponent,
    BarComponent,
    BeerComponent,
    DrinkerComponent,
    FilterPipe,
    BarDetailsComponent,
    DrinkerDetailsComponent,
    BeerDetailsComponent,
    ModsComponent,
    SqlComponent,
    SqlPipe,
    BillDetailsComponent,
    VerifyComponent
  ],
  imports: [BrowserModule, AppRoutingModule, HttpClientModule, FormsModule, TableModule, DropdownModule, BrowserAnimationsModule],
  providers: [HttpClientModule],
  bootstrap: [AppComponent]
})
export class AppModule {}
