import { Component, Input } from '@angular/core';

@Component({
  standalone: false,
  selector: 'app-tac-view',
  template: `
    <div *ngIf="instructions.length > 0" class="section">
      <h3>Three-Address Code (TAC)</h3>
      <div class="code-box">
        <div *ngFor="let line of instructions"><code>{{ line }}</code></div>
      </div>
    </div>
  `,
  styles: [`
    .code-box { background: #272822; color: #a6e22e; padding: 15px; border-radius: 4px; font-family: monospace; font-size: 15px; line-height: 1.5; }
  `]
})
export class TacViewComponent {
  @Input() instructions: string[] = [];
}