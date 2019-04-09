import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';
import { DrinkerComponent } from './drinker/drinker.component';
import { BarComponent } from './bar/bar.component';
import { BeerComponent } from './beer/beer.component';
import { BarDetailsComponent } from './bar-details/bar-details.component';
import { DrinkerDetailsComponent } from './drinker-details/drinker-details.component';
import { BillDetailsComponent } from './bill-details/bill-details.component';
import { BeerDetailsComponent } from './beer-details/beer-details.component';
import { ModsComponent } from './mods/mods.component';
import { SqlComponent } from './sql/sql.component';
import { VerifyComponent } from './verify/verify.component';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'drinker',
    pathMatch: 'full'
  },
  {
    path: 'drinker',
    pathMatch: 'full',
    component: DrinkerComponent
  },
  {
    path: 'drinker/:id',
    pathMatch: 'full',
    component: DrinkerDetailsComponent
  },
  {
    path: 'drinker/billing/:id',
    pathMatch: 'full',
    component: BillDetailsComponent
  },
  {
    path: 'bar',
    pathMatch: 'full',
    component: BarComponent
  },
  {
    path: 'bar/:id',
    pathMatch: 'full',
    component: BarDetailsComponent
  },
  {
    path: 'beer',
    pathMatch: 'full',
    component: BeerComponent
  },
  {
    path: 'beer/:id',
    pathMatch: 'full',
    component: BeerDetailsComponent
  },
  {
    path: 'mods',
    pathMatch: 'full',
    component: ModsComponent
  },
  {
    path: 'sql',
    pathMatch: 'full',
    component: SqlComponent
  },
  {
    path: 'verify',
    pathMatch: 'full',
    component: VerifyComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule {}
