import mitsuba as mi
mi.set_variant('scalar_rgb')

filename = 'reference.xml'
scene = mi.load_file(filename)
img=mi.render(scene)
mi.Bitmap(img).write('reference.exr')