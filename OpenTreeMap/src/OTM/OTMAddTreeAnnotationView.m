// This file is part of the OpenTreeMap code.
//
// OpenTreeMap is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// OpenTreeMap is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with OpenTreeMap.  If not, see <http://www.gnu.org/licenses/>.

#import "OTMAddTreeAnnotationView.h"

@implementation OTMAddTreeAnnotationView

@synthesize mapView, delegate;

- (id)initWithAnnotation:(id <MKAnnotation>)annotation reuseIdentifier:(NSString *)reuseIdentifier {
	self = [super initWithAnnotation:annotation reuseIdentifier:reuseIdentifier];
    
	if (self) {
		self.image = [UIImage imageNamed:@"handle_icon"];
        [self clearTouch];
	}
	return self;
}

/**
 Set the touchXOffset and touchYOffset members by calculating the distance from the
 the touch to the center of the annotation view.
 */
- (void)setOffsetsFromTouch:(UITouch *)touch
{
    CGPoint point = [touch locationInView:self];
    touchXOffset = point.x - self.bounds.size.width / 2.0;
    touchYOffset = point.y - self.bounds.size.height / 2.0;
}

/**
 Set the coordinate of the MKPointAnnotation by adding the touchXOffset and
 touchYOffset to the touch and then using the MKMapView to translate the pixel
 location to a map coordinate.
 */
- (void)updateCoordinateFromTouch:(UITouch *)touch
{
    CGPoint point = [touch locationInView:nil]; // nil means "use the application window"
    point.x -= touchXOffset;
    point.y -= touchYOffset;
    CLLocationCoordinate2D newCoordinate = [mapView convertPoint:point
                                            toCoordinateFromView:nil]; // nil means "use the application window"
    self.annotation.coordinate = newCoordinate;
}

/**
 Reset the touch tracking member variables to an initial state.
 */
- (void)clearTouch
{
    isMoving = NO;
    touchXOffset = 0.0;
    touchYOffset = 0.0;
}

#pragma mark UIResponder delgate methods

-(void)touchesBegan:(NSSet*)touches withEvent:(UIEvent*)event
{
    isMoving = YES;
    [self setOffsetsFromTouch:[[event allTouches] anyObject]];
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event 
{
    if (isMoving) {
        [self updateCoordinateFromTouch:[[event allTouches] anyObject]];
    } else {
        [super touchesMoved:touches withEvent:event];
    }
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self clearTouch];
    [self.delegate movedAnnotation:self.annotation];
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [self clearTouch];
}

@end
