import { ComponentFixture, TestBed } from '@angular/core/testing';
import { Benchmark } from './benchmark';

describe('Benchmark', () => {
  let component: Benchmark;
  let fixture: ComponentFixture<Benchmark>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [Benchmark],
    }).compileComponents();

    fixture = TestBed.createComponent(Benchmark);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
