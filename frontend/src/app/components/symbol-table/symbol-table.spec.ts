import { ComponentFixture, TestBed } from '@angular/core/testing';
import { SymbolTable } from './symbol-table';

describe('SymbolTable', () => {
  let component: SymbolTable;
  let fixture: ComponentFixture<SymbolTable>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [SymbolTable],
    }).compileComponents();

    fixture = TestBed.createComponent(SymbolTable);
    component = fixture.componentInstance;
    await fixture.whenStable();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
