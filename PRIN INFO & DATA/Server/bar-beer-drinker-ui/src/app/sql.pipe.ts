import { Pipe, PipeTransform } from '@angular/core';

@Pipe({
  name: 'sql'
})
export class SqlPipe implements PipeTransform {

  transform(value: any, args?: any): any {
    return null;
  }

}
