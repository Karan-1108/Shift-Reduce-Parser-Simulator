import { Component, Input } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-tac-view',
  templateUrl: './tac-view.html',
  styleUrls: ['./tac-view.css']
})
export class TacViewComponent {
  @Input() instructions: string[] = [];
}