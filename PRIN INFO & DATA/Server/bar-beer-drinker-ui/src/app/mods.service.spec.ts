import { TestBed } from '@angular/core/testing';

import { ModsService } from './mods.service';

describe('ModsService', () => {
  beforeEach(() => TestBed.configureTestingModule({}));

  it('should be created', () => {
    const service: ModsService = TestBed.get(ModsService);
    expect(service).toBeTruthy();
  });
});
