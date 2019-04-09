import { SqlPipe } from './sql.pipe';

describe('SqlPipe', () => {
  it('create an instance', () => {
    const pipe = new SqlPipe();
    expect(pipe).toBeTruthy();
  });
});
