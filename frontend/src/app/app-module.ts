import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { HttpClientModule } from '@angular/common/http';

import { AppComponent } from './app';
import { ControlPanelComponent } from './components/control-panel/control-panel';
import { TraceTableComponent } from './components/trace-table/trace-table';
import { SymbolTableComponent } from './components/symbol-table/symbol-table';
import { TacViewComponent } from './components/tac-view/tac-view';
import { BenchmarkComponent } from './components/benchmark/benchmark';

@NgModule({
  declarations: [
    AppComponent,
    ControlPanelComponent,
    TraceTableComponent,
    SymbolTableComponent,
    TacViewComponent,
    BenchmarkComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }