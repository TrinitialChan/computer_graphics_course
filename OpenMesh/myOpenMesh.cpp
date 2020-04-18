void MeshViewerWidget::DrawBoundingSphere(void) const
{
	Mesh::VertexIter vlt, vBegin, vEnd;
	vBegin = mesh.vertices_begin();
	vEnd = mesh.vertices_end();

	
	
	//初始化第一个球
	
	MeshTraits::Point maxpoint;
	MeshTraits::Point maxX,minX,maxY,minY,maxZ,minZ;
	double maxX_x = -1, maxY_y = -1, maxZ_z = -1;
	double minX_x = 1, minY_y = 1, minZ_z = 1;
	for (vlt = vBegin; vlt != vEnd; ++vlt) {
		MeshTraits::Point point = mesh.point(*vlt);

		if (point.data()[0] > maxX_x) { maxX_x = point.data()[0]; maxX = point; }
		if (point.data()[0] < minX_x) { minX_x = point.data()[0]; minX = point; }

		if (point.data()[1] > maxY_y) { maxY_y = point.data()[1]; maxY = point; }
		if (point.data()[1] < minY_y) { minY_y = point.data()[1]; minY = point; }

		if (point.data()[2] > maxZ_z) { maxZ_z = point.data()[2]; maxZ = point; }
		if (point.data()[2] < minZ_z) { minZ_z = point.data()[2]; minZ = point; }

	}

	//绘制极大点
	DrawMyPoint(maxX.data()[0], maxX.data()[1], maxX.data()[2], 0.8, 0, 0);
	DrawMyPoint(minX.data()[0], minX.data()[1], minX.data()[2], 0.8, 0, 0);

	DrawMyPoint(maxY.data()[0], maxY.data()[1], maxY.data()[2], 0.8, 0, 0);
	DrawMyPoint(minY.data()[0], minY.data()[1], minY.data()[2], 0.8, 0, 0);

	DrawMyPoint(maxZ.data()[0], maxZ.data()[1], maxZ.data()[2], 0.8, 0, 0);
	DrawMyPoint(minZ.data()[0], minZ.data()[1], minZ.data()[2], 0.8, 0, 0);

	double x=0, y=0, z=0;
	x = sqrt(pow((maxX.data()[0] - minX.data()[0]), 2) + pow((maxX.data()[1] - minX.data()[1]), 2) + pow((maxX.data()[2] - minX.data()[2]), 2));
	y = sqrt(pow((maxY.data()[0] - minY.data()[0]), 2) + pow((maxY.data()[1] - minY.data()[1]), 2) + pow((maxY.data()[2] - minY.data()[2]), 2));
	z = sqrt(pow((maxZ.data()[0] - minZ.data()[0]), 2) + pow((maxZ.data()[1] - minZ.data()[1]), 2) + pow((maxZ.data()[2] - minZ.data()[2]), 2));

	float dia = 0;
	MeshTraits::Point max = maxX, min = minX;
	dia = x;
	if (z > x && z > y)
	{
		max = maxZ;
		min = minZ;
		dia = z;
	}
	else if (y > x && y > z)
	{
		max = maxY;
		min = minY;
		dia = y;
	}

	//初始球心
	double tempx, tempy, tempz;
	double tempRadius;
	tempx = 0.5*(max.data()[0] + min.data()[0]);
	tempy = 0.5*(max.data()[1] + min.data()[1]);
	tempz = 0.5*(max.data()[2] + min.data()[2]);
	
	//初始球半径
	tempRadius = dia/2;

	//绘制初始球心
	std::cout << "初始球心是:\n" << tempx << "\t" << tempy << "\t" << tempz << std::endl;
	DrawMyPoint(tempx, tempy, tempz, 1, 0.3, 0.5);
	std::cout << "初始半径是:\t" << tempRadius << std::endl;

	//开始修正
	for (vlt = vBegin; vlt != vEnd; ++vlt) {
		MeshTraits::Point point = mesh.point(*vlt);
		double x, y, z;
		x = point.data()[0]; y = point.data()[1]; z = point.data()[2];
		double dist = sqrt(pow((tempx - x), 2) + pow((tempy - y), 2) + pow((tempz - z), 2));

		if (dist > tempRadius) {
			DrawMyPoint(x, y, z,0.8,0,0.8);
			double bias = (dist - tempRadius)/2;
			tempx += (x - tempx)*bias / dist;
			tempy += (y - tempy)*bias / dist;
			tempz += (z - tempz)*bias / dist;
			tempRadius = (dist + tempRadius) / 2;
		}

	}
	//修正完成，标注球心
	DrawMyPoint(tempx, tempy, tempz,0.8,0.8,0);
	std::cout <<"修正球心是:\n"<< tempx << "\t"<<tempy << "\t" << tempz << std::endl;
	std::cout << "修正半径是:\t" << tempRadius << std::endl;

	//定义半径
	double radius;
	
	//定义球心
	double center_x, center_y, center_z=0;
	
	//传参
	center_x = tempx;
	center_y = tempy;
	center_z = tempz;
	radius = tempRadius;

	//绘制经纬线型
	glLineWidth(0.1f);
	glPointSize(1.0);
	glColor3d(.0, .0, .3);
	for (double j = -radius; j <= radius; j += 0.04) {
		double layer_radius = sqrt(radius*radius - j * j);

		glBegin(GL_LINE_STRIP);
		for (double i = 0; i <= 3.1415 * 2; i += 0.01)
		{
			glVertex3d(	layer_radius*sin(i)+ center_x ,
						j + center_y, 
						layer_radius*cos(i) + center_z);
		}
		glEnd();
	}

	for (double j = 0; j < 3.1415; j += 0.03) {
		glBegin(GL_LINE_STRIP);
		for (double i = 0; i <= 3.1415 * 2; i += 0.01)
		{
			glVertex3d(	radius*cos(j)*cos(i) + center_x, 
						radius*sin(i) + center_y, 
						radius*sin(j)*cos(i) + center_z);
		}
		glEnd();
	}

}
void MeshViewerWidget::DrawVertexNormalVector(void) const 
{

	Mesh::VertexIter vlt, vBegin, vEnd;
	vBegin = mesh.vertices_begin();
	vEnd = mesh.vertices_end();

	for (vlt = vBegin; vlt != vEnd; ++vlt) {
		MeshTraits::Point point = mesh.point(*vlt);
		//auto vertex = mesh.vertex(*vlt);
		OpenMesh::VertexHandle vertex = *vlt;
		
		//for (auto it = mesh.cvf_begin(vertex); it != mesh.cvf_end(vertex); ++it) {}

		Mesh::VertexFaceIter vflt, vfBegin, vfEnd;
		vfBegin = mesh.cvf_begin(*vlt);
		vfEnd = mesh.cvf_end(*vlt);
		double sum = 0;
		double dotx=0, doty=0, dotz=0;
		for (vflt= vfBegin; vflt != vfEnd; ++vflt) {

			//auto face = vflt.handle();
			//MyMesh::Face face = mesh.face(*vflt);
			auto normal = mesh.normal(*vflt);
			double x = normal.data()[0];
			double y = normal.data()[1];
			double z = normal.data()[2];
			
			dotx += x;
			doty += y;
			dotz += z;
			sum++;
		}
		double myMod = sqrt(dotx * dotx + doty * doty + dotz * dotz);
		myMod;
		dotx /= myMod;
		doty /= myMod;
		dotz /= myMod;
		double ratio = 0.01;
		dotx *= ratio;
		doty *= ratio;
		dotz *= ratio;
		DrawMyLine(point.data()[0], point.data()[1], point.data()[2], point.data()[0] + dotx, point.data()[1] + doty, point.data()[2] + dotz);
		DrawMyLine(point.data()[0], point.data()[1], point.data()[2], point.data()[0] - dotx, point.data()[1] - doty, point.data()[2] - dotz);
		//std::cout << sum << std::endl;

	}

}