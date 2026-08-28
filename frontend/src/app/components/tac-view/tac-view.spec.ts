import { ComponentFixture, TestBed } from '@angular/core/testing';
import { TacView } from './tac-view';

describe('TacView', () => {
  let component: TacView;
  let fixture: ComponentFixture<TacView>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [TacView],
    }).compileComponents();

    fixture = TestBed.createComponent(TacView);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
