import { ComponentFixture, TestBed } from '@angular/core/testing';
import { TraceTable } from './trace-table';

describe('TraceTable', () => {
  let component: TraceTable;
  let fixture: ComponentFixture<TraceTable>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [TraceTable],
    }).compileComponents();

    fixture = TestBed.createComponent(TraceTable);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
