bunnyRead = open('../resources/bun_zipper.ply', 'r')
bunnyWrite = open('../resources/bun_zipper_simplified.txt', 'w') # no se si es realmente un formato

vertexTotal = 35947
faceTotal = 69451

vertices = []
faces = []

for line in bunnyRead:
    if line == 'property float confidence\n':
        continue
    if line == 'property float intensity\n':
        continue
    if line == 'end_header\n':
        break

for i in range(vertexTotal):
    splitted = bunnyRead.readline().split(' ')
    parsed = splitted[0]+' '+splitted[1]+' '+splitted[2]+'\n'
    vertices.append([float(splitted[0]), float(splitted[1]), float(splitted[2])])

for line in bunnyRead:
    splitted = bunnyRead.readline().split(' ')
    if splitted == ['']:
        break
    faces.append([int(splitted[1]), int(splitted[2]), int(splitted[3])])

bunnyRead.close()
bunnyRead = open('../resources/bun_zipper.ply', 'r')


def calcNormal(face):
    a, b, c = [vertices[face[0]], vertices[face[1]], vertices[face[2]]]
    ab = [b[0]-a[0], b[1]-a[1], b[2]-a[2]]
    ac = [c[0]-a[0], c[1]-a[1], c[2]-a[2]]

    x = ab[1]*ac[2]-(ab[2]*ac[1])
    y = -(ab[0]*ac[2]-(ab[2]*ac[0]))
    z = ab[0]*ac[1]-(ab[1]*ac[0])
    return [x, y, z]


new_vertices = []

for face in faces:
    normal = calcNormal(face)
    new_vertices.append([vertices[face[0]][0], vertices[face[0]][1], vertices[face[0]][2], normal[0], normal[1], normal[2]])
    new_vertices.append([vertices[face[1]][0], vertices[face[1]][1], vertices[face[1]][2], normal[0], normal[1], normal[2]])
    new_vertices.append([vertices[face[2]][0], vertices[face[2]][1], vertices[face[2]][2], normal[0], normal[1], normal[2]])

for i in range(len(new_vertices)):
    for j in range(len(new_vertices[i])):
        x = new_vertices[i][j]
        if j > 2:
            x = '{:.{prec}f}'.format(x, prec=15)
        else:
            x = str(x)
        new_vertices[i][j] = x

new_vertex_total = len(new_vertices)

bunnyWrite.write(str(new_vertex_total) + '\n')

for line in bunnyRead:
    if line == 'end_header\n':
        break

for i in range(new_vertex_total):
    string = new_vertices[i][0]+' '+new_vertices[i][1]+' '+new_vertices[i][2]+' '+new_vertices[i][3]+' '+new_vertices[i][4]+' '+new_vertices[5][1] + '\n'
    bunnyWrite.write(string)

bunnyRead.close()
bunnyWrite.close()
