using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Windows.Forms.VisualStyles;

namespace SlimGen
{
    public enum ToolbarTheme
    {
        Toolbar,
        MediaToolbar,
        CommunicationsToolbar,
        BrowserTabBar,
        HelpBar
    }

    public class ToolStripNativeRenderer : ToolStripSystemRenderer
    {
        VisualStyleRenderer renderer;

        public static bool IsSupported
        {
            get
            {
                if (!VisualStyleRenderer.IsSupported)
                    return false;

                return VisualStyleRenderer.IsElementDefined(VisualStyleElement.CreateElement("Menu", 7, 1));
            }
        }

        public ToolStripNativeRenderer(ToolbarTheme theme)
        {
            Theme = theme;
        }

        static internal class NativeMethods
        {
            [StructLayout(LayoutKind.Sequential, Pack = 1)]
            public struct MARGINS
            {
                public int cxLeftWidth;
                public int cxRightWidth;
                public int cyTopHeight;
                public int cyBottomHeight;
            }

            [DllImport("uxtheme.dll", ExactSpelling = true)]
            public extern static int GetThemeMargins(IntPtr hTheme, IntPtr hdc, int iPartId, int iStateId, int iPropId, IntPtr rect, out MARGINS pMargins);
        }

        enum MenuParts
        {
            ItemTMSchema = 1,
            DropDownTMSchema = 2,
            BarItemTMSchema = 3,
            BarDropDownTMSchema = 4,
            ChevronTMSchema = 5,
            SeparatorTMSchema = 6,
            BarBackground = 7,
            BarItem = 8,
            PopupBackground = 9,
            PopupBorders = 10,
            PopupCheck = 11,
            PopupCheckBackground = 12,
            PopupGutter = 13,
            PopupItem = 14,
            PopupSeparator = 15,
            PopupSubmenu = 16,
            SystemClose = 17,
            SystemMaximize = 18,
            SystemMinimize = 19,
            SystemRestore = 20
        }

        enum MenuBarStates
        {
            Active = 1,
            Inactive = 2
        }

        enum MenuBarItemStates
        {
            Normal = 1,
            Hover = 2,
            Pushed = 3,
            Disabled = 4,
            DisabledHover = 5,
            DisabledPushed = 6
        }

        enum MenuPopupItemStates
        {
            Normal = 1,
            Hover = 2,
            Disabled = 3,
            DisabledHover = 4
        }

        enum MenuPopupCheckStates
        {
            CheckmarkNormal = 1,
            CheckmarkDisabled = 2,
            BulletNormal = 3,
            BulletDisabled = 4
        }

        enum MenuPopupCheckBackgroundStates
        {
            Disabled = 1,
            Normal = 2,
            Bitmap = 3
        }

        enum MenuPopupSubMenuStates
        {
            Normal = 1,
            Disabled = 2
        }

        enum MarginTypes
        {
            Sizing = 3601,
            Content = 3602,
            Caption = 3603
        }

        const int RebarBackground = 6;

        Padding GetThemeMargins(IDeviceContext dc, MarginTypes marginType)
        {
            NativeMethods.MARGINS margins;
            try
            {
                IntPtr hDC = dc.GetHdc();
                if (0 == NativeMethods.GetThemeMargins(renderer.Handle, hDC, renderer.Part, renderer.State, (int)marginType, IntPtr.Zero, out margins))
                    return new Padding(margins.cxLeftWidth, margins.cyTopHeight, margins.cxRightWidth, margins.cyBottomHeight);
                return new Padding(-1);
            }
            finally
            {
                dc.ReleaseHdc();
            }
        }

        static int GetItemState(ToolStripItem item)
        {
            bool hot = item.Selected;

            if (item.Owner.IsDropDown)
            {
                if (item.Enabled)
                    return hot ? (int)MenuPopupItemStates.Hover : (int)MenuPopupItemStates.Normal;
                return hot ? (int)MenuPopupItemStates.DisabledHover : (int)MenuPopupItemStates.Disabled;
            }
            else
            {
                if (item.Pressed)
                    return item.Enabled ? (int)MenuBarItemStates.Pushed : (int)MenuBarItemStates.DisabledPushed;
                if (item.Enabled)
                    return hot ? (int)MenuBarItemStates.Hover : (int)MenuBarItemStates.Normal;
                return hot ? (int)MenuBarItemStates.DisabledHover : (int)MenuBarItemStates.Disabled;
            }
        }

        public ToolbarTheme Theme
        {
            get;
            set;
        }

        string RebarClass
        {
            get { return SubclassPrefix + "Rebar"; }
        }

        string ToolbarClass
        {
            get { return SubclassPrefix + "ToolBar"; }
        }

        string MenuClass
        {
            get { return SubclassPrefix + "Menu"; }
        }

        string SubclassPrefix
        {
            get
            {
                switch (Theme)
                {
                    case ToolbarTheme.MediaToolbar: return "Media::";
                    case ToolbarTheme.CommunicationsToolbar: return "Communications::";
                    case ToolbarTheme.BrowserTabBar: return "BrowserTabBar::";
                    case ToolbarTheme.HelpBar: return "Help::";
                    default: return string.Empty;
                }
            }
        }

        VisualStyleElement Subclass(VisualStyleElement element)
        {
            return VisualStyleElement.CreateElement(SubclassPrefix + element.ClassName,
                    element.Part, element.State);
        }

        private bool EnsureRenderer()
        {
            if (!IsSupported)
                return false;

            if (renderer == null)
                renderer = new VisualStyleRenderer(VisualStyleElement.Button.PushButton.Normal);

            return true;
        }

        protected override void Initialize(ToolStrip toolStrip)
        {
            if (toolStrip.Parent is ToolStripPanel)
                toolStrip.BackColor = Color.Transparent;

            base.Initialize(toolStrip);
        }

        protected override void InitializePanel(ToolStripPanel toolStripPanel)
        {
            foreach (Control control in toolStripPanel.Controls)
                if (control is ToolStrip)
                    Initialize((ToolStrip)control);

            base.InitializePanel(toolStripPanel);
        }


        protected override void OnRenderToolStripBorder(ToolStripRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                renderer.SetParameters(MenuClass, (int)MenuParts.PopupBorders, 0);
                if (e.ToolStrip.IsDropDown)
                {
                    Region oldClip = e.Graphics.Clip;
                    Rectangle insideRect = e.ToolStrip.ClientRectangle;
                    insideRect.Inflate(-1, -1);
                    e.Graphics.ExcludeClip(insideRect);

                    renderer.DrawBackground(e.Graphics, e.ToolStrip.ClientRectangle, e.AffectedBounds);
                    e.Graphics.Clip = oldClip;
                }
            }
            else
            {
                base.OnRenderToolStripBorder(e);
            }
        }

        protected override void OnRenderMenuItemBackground(ToolStripItemRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                int partID = e.Item.Owner.IsDropDown ? (int)MenuParts.PopupItem : (int)MenuParts.BarItem;
                renderer.SetParameters(MenuClass, partID, GetItemState(e.Item));

                Rectangle bgRect = e.Item.ContentRectangle;
                if (!e.Item.Owner.IsDropDown)
                    bgRect = new Rectangle(new Point(), e.Item.Bounds.Size);

                renderer.DrawBackground(e.Graphics, bgRect, bgRect);
            }
            else
            {
                base.OnRenderMenuItemBackground(e);
            }
        }

        protected override void OnRenderToolStripPanelBackground(ToolStripPanelRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                if (VisualStyleRenderer.IsElementDefined(VisualStyleElement.CreateElement(RebarClass, RebarBackground, 0)))
                {
                    renderer.SetParameters(RebarClass, RebarBackground, 0);
                }
                else
                {
                    renderer.SetParameters(RebarClass, 0, 0);
                }

                if (renderer.IsBackgroundPartiallyTransparent())
                    renderer.DrawParentBackground(e.Graphics, e.ToolStripPanel.ClientRectangle, e.ToolStripPanel);

                renderer.DrawBackground(e.Graphics, e.ToolStripPanel.ClientRectangle);
                e.Handled = true;
            }
            else
            {
                base.OnRenderToolStripPanelBackground(e);
            }
        }

        protected override void OnRenderToolStripBackground(System.Windows.Forms.ToolStripRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                if (e.ToolStrip.IsDropDown)
                {
                    renderer.SetParameters(MenuClass, (int)MenuParts.PopupBackground, 0);
                }
                else
                {
                    if (e.ToolStrip.Parent is ToolStripPanel)
                    {
                        return;
                    }
                    else
                    {
                        if (VisualStyleRenderer.IsElementDefined(VisualStyleElement.CreateElement(RebarClass, RebarBackground, 0)))
                            renderer.SetParameters(RebarClass, RebarBackground, 0);
                        else
                            renderer.SetParameters(RebarClass, 0, 0);
                    }
                }

                if (renderer.IsBackgroundPartiallyTransparent())
                    renderer.DrawParentBackground(e.Graphics, e.ToolStrip.ClientRectangle, e.ToolStrip);

                renderer.DrawBackground(e.Graphics, e.ToolStrip.ClientRectangle, e.AffectedBounds);
            }
            else
            {
                base.OnRenderToolStripBackground(e);
            }
        }

        protected override void OnRenderSplitButtonBackground(ToolStripItemRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                ToolStripSplitButton sb = (ToolStripSplitButton)e.Item;
                base.OnRenderSplitButtonBackground(e);

                OnRenderArrow(new ToolStripArrowRenderEventArgs(e.Graphics, sb, sb.DropDownButtonBounds, Color.Red, ArrowDirection.Down));
            }
            else
            {
                base.OnRenderSplitButtonBackground(e);
            }
        }

        Color GetItemTextColor(ToolStripItem item)
        {
            int partId = item.IsOnDropDown ? (int)MenuParts.PopupItem : (int)MenuParts.BarItem;
            renderer.SetParameters(MenuClass, partId, GetItemState(item));
            return renderer.GetColor(ColorProperty.TextColor);
        }

        protected override void OnRenderItemText(ToolStripItemTextRenderEventArgs e)
        {
            if (EnsureRenderer())
                e.TextColor = GetItemTextColor(e.Item);

            base.OnRenderItemText(e);
        }

        protected override void OnRenderImageMargin(ToolStripRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                if (e.ToolStrip.IsDropDown)
                {
                    renderer.SetParameters(MenuClass, (int)MenuParts.PopupGutter, 0);

                    int extraWidth = (e.ToolStrip.Width - e.ToolStrip.DisplayRectangle.Width) - e.AffectedBounds.Width;
                    Rectangle rect = e.AffectedBounds;
                    rect.Y += 2;
                    rect.Height -= 4;
                    int sepWidth = renderer.GetPartSize(e.Graphics, ThemeSizeType.True).Width;
                    if (e.ToolStrip.RightToLeft == RightToLeft.Yes)
                    {
                        rect = new Rectangle(rect.X - extraWidth, rect.Y, sepWidth, rect.Height);
                        rect.X += sepWidth;
                    }
                    else
                    {
                        rect = new Rectangle(rect.Width + extraWidth - sepWidth, rect.Y, sepWidth, rect.Height);
                    }
                    renderer.DrawBackground(e.Graphics, rect);
                }
            }
            else
            {
                base.OnRenderImageMargin(e);
            }
        }

        protected override void OnRenderSeparator(ToolStripSeparatorRenderEventArgs e)
        {
            if (e.ToolStrip.IsDropDown && EnsureRenderer())
            {
                renderer.SetParameters(MenuClass, (int)MenuParts.PopupSeparator, 0);
                Rectangle rect = new Rectangle(e.ToolStrip.DisplayRectangle.Left, 0, e.ToolStrip.DisplayRectangle.Width, e.Item.Height);
                renderer.DrawBackground(e.Graphics, rect, rect);
            }
            else
            {
                base.OnRenderSeparator(e);
            }
        }

        protected override void OnRenderItemCheck(ToolStripItemImageRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                Rectangle rect = e.Item.ContentRectangle;
                rect.Width = rect.Height;
                if (e.Item.RightToLeft == RightToLeft.Yes)
                    rect = new Rectangle(e.ToolStrip.ClientSize.Width - rect.X - rect.Width, rect.Y, rect.Width, rect.Height);

                renderer.SetParameters(MenuClass, (int)MenuParts.PopupCheckBackground, e.Item.Enabled ? (int)MenuPopupCheckBackgroundStates.Normal : (int)MenuPopupCheckBackgroundStates.Disabled);
                renderer.DrawBackground(e.Graphics, rect);

                Padding margins = GetThemeMargins(e.Graphics, MarginTypes.Sizing);

                rect = new Rectangle(rect.X + margins.Left, rect.Y + margins.Top,
                        rect.Width - margins.Horizontal,
                        rect.Height - margins.Vertical);

                renderer.SetParameters(MenuClass, (int)MenuParts.PopupCheck, e.Item.Enabled ? (int)MenuPopupCheckStates.CheckmarkNormal : (int)MenuPopupCheckStates.CheckmarkDisabled);

                renderer.DrawBackground(e.Graphics, rect);
            }
            else
            {
                base.OnRenderItemCheck(e);
            }
        }

        protected override void OnRenderArrow(ToolStripArrowRenderEventArgs e)
        {
            if (EnsureRenderer())
                e.ArrowColor = GetItemTextColor(e.Item);
            base.OnRenderArrow(e);
        }

        protected override void OnRenderOverflowButtonBackground(ToolStripItemRenderEventArgs e)
        {
            if (EnsureRenderer())
            {
                string rebarClass = RebarClass;
                if (Theme == ToolbarTheme.BrowserTabBar)
                    rebarClass = "Rebar";

                int state = VisualStyleElement.Rebar.Chevron.Normal.State;
                if (e.Item.Pressed)
                    state = VisualStyleElement.Rebar.Chevron.Pressed.State;
                else if (e.Item.Selected)
                    state = VisualStyleElement.Rebar.Chevron.Hot.State;

                renderer.SetParameters(rebarClass, VisualStyleElement.Rebar.Chevron.Normal.Part, state);
                renderer.DrawBackground(e.Graphics, new Rectangle(Point.Empty, e.Item.Size));
            }
            else
            {
                base.OnRenderOverflowButtonBackground(e);
            }
        }
    }
}
