from gi.repository import Gtk

from graphutils import Polyhedron, Polygon, Viewport, Vector, Camera
from drawer import Drawer

class MainWindowHandler:
    def __init__(self):
        self._init_polygons()
        self._init_ui()

    def _init_ui(self):
        self.builder = Gtk.Builder()
        self.builder.add_from_file("mainwindow.glade")
        self.builder.connect_signals(self)

        self.win = self.builder.get_object("main_window")
        self.xmin_spin = self.builder.get_object("xmin_spin")
        self.xmax_spin = self.builder.get_object("xmax_spin")
        self.camx_spin = self.builder.get_object("camx_spin")
        self.camy_spin = self.builder.get_object("camy_spin")
        self.camz_spin = self.builder.get_object("camz_spin")
        self.d_spin = self.builder.get_object("d_spin")
        self.originx_spin = self.builder.get_object("originx_spin")
        self.originy_spin = self.builder.get_object("originy_spin")
        self.originz_spin = self.builder.get_object("originz_spin")

    def _init_polygons(self):
        self.polyhedron = Polyhedron([
            Polygon([
                Vector(0, 0, 0),
                Vector(1, 0, 0),
                Vector(1, 1, 0),
                Vector(0, 1, 0),
            ]),
            Polygon([
                Vector(0, 0, 1),
                Vector(1, 0, 1),
                Vector(1, 1, 1),
                Vector(0, 1, 1),
            ]),
            Polygon([
                Vector(0, 0, 0),
                Vector(0, 0, 1),
                Vector(0, 1, 1),
                Vector(0, 1, 0),
            ]),
            Polygon([
                Vector(1, 0, 0),
                Vector(1, 0, 1),
                Vector(1, 1, 1),
                Vector(1, 1, 0),
            ]),
            Polygon([
                Vector(0, 0, 0),
                Vector(1, 0, 0),
                Vector(1, 0, 1),
                Vector(0, 0, 1),
            ]),
            Polygon([
                Vector(0, 1, 0),
                Vector(1, 1, 0),
                Vector(1, 1, 1),
                Vector(0, 1, 1),
            ]),
        ])

    def run(self):
        self.win.show_all()
        Gtk.main()

    def on_window_delete(self, *args):
        Gtk.main_quit(*args)

    def on_drawing_area_draw(self, da, ctx):
        r = da.get_allocation()
        (xmin, xmax) = (self.xmin_spin.get_value(), self.xmax_spin.get_value())
        (ymin, ymax) = (xmin * r.height / r.width, xmax * r.height / r.width)

        viewport = Viewport(
            Camera(
                Vector(self.camx_spin.get_value(),
                       self.camy_spin.get_value(),
                       self.camz_spin.get_value()),
                Vector(self.originx_spin.get_value(),
                       self.originy_spin.get_value(),
                       self.originz_spin.get_value()),
                self.d_spin.get_value(),
                Vector(0, 0, 1)
            ),
            xmin,
            xmax,
            ymin,
            ymax
        )
        ctx.set_line_width(1)

        drw = Drawer(viewport, da, ctx)
        drw.draw_mesh()
        drw.draw_polyhedron(self.polyhedron)

    def on_spin_value_changed(self, obj):
        self.win.queue_draw()
